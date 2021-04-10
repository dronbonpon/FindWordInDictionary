#include <gtk/gtk.h>

#include "../include/initialize_dict.h"
#include "../include/error.h"
#include "../include/utils.h"
#include "../include/dictionary_utils.h"
#include "../include/config.h"
#include "../include/logger.h"
#include "../include/result.h"

#include <string>
#include <variant>
#include <vector>
#include <optional>
#include <iostream>

namespace
{

static GtkWidget *findWords;

void OpenResultWindow( GtkWidget *calculate, gpointer data, 
                       std::string& resultStr )
{
    GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
    gtk_window_set_default_size ( GTK_WINDOW ( window ), 800, 600 );

    GtkWidget *hbox = gtk_box_new( GTK_ORIENTATION_HORIZONTAL, 4 );

    GtkWidget* scrolledwindow_text = gtk_scrolled_window_new( NULL, NULL );
    GtkWidget *textview = gtk_text_view_new();
    gtk_text_buffer_set_text(
            gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview)), resultStr.c_str(), -1 );

    gtk_container_add( GTK_CONTAINER( window ), hbox );

    gtk_container_add( GTK_CONTAINER( scrolledwindow_text ), textview );
    gtk_box_pack_start( GTK_BOX( hbox ), scrolledwindow_text, 1, 4, 10 );

    gtk_widget_show_all( window );
}

void FindSubsequences( GtkWidget *calculate, gpointer data )
{
    std::string word = ( char * )gtk_entry_get_text( GTK_ENTRY( findWords ) );

    std::string resultStr;
    
    result::ForSubsequences( resultStr, word );

    OpenResultWindow( calculate, data, resultStr );
}

void FindSubstr( GtkWidget *calculate, gpointer data )
{
    std::string word = ( char * )gtk_entry_get_text( GTK_ENTRY( findWords ) );

    std::string resultStr;
    
    result::ForSubstrings( resultStr, word );

    OpenResultWindow( calculate, data, resultStr );
}

} // nameless namespace

int main( int argc, char **argv ) 
{
    if ( argc < 2 )
    {
        std::cerr << "Can't open config file" << std::endl;
        return -1;
    }

    std::optional<ErrorCode> configInitStatus = 
                             ConfigManager::GetInstance().Initialize( argv[1] );
    
    if ( configInitStatus != std::nullopt )
    {
        std::cerr << GetErrorMessage( configInitStatus.value() ) << std::endl;
        return -1;
    }
    LogInfo( "Config manager initialized" );

    Logger::GetInstance().Initialize();
    LogInfo( "Logger initialized" );

    std::string dictFileName = ConfigManager::GetInstance().GetDictionaryName();
    std::string dictFilePath = ConfigManager::GetInstance().GetDictionaryPath();

    std::optional<ErrorCode> dictionatyInitStatus = 
                             DictionaryUtils::GetInstance().Initialize( dictFileName, dictFilePath );
    
    if ( dictionatyInitStatus != std::nullopt )
    {
        LogError( GetErrorMessage( dictionatyInitStatus.value() ) );
        return -1;
    }
    LogInfo( "Dictionary has loaded" );

    GtkWidget *window, *grid, *findSubStrButton, *findSubSeqButton;
    gtk_init( &argc, &argv );

    window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
    gtk_window_set_default_size( GTK_WINDOW ( window ), 400, 100 );
    g_signal_connect( window, "destroy", G_CALLBACK( gtk_main_quit ), NULL );

    GtkWidget *hbox = gtk_box_new( GTK_ORIENTATION_HORIZONTAL, 4 );

    grid = gtk_grid_new();
    gtk_container_add( GTK_CONTAINER( window ), grid );

    findWords = gtk_entry_new();
    gtk_grid_attach( GTK_GRID( grid ), findWords, 0, 0, 1, 1 );

    findSubStrButton = gtk_button_new_with_label( "Find if substring" );
    g_signal_connect( findSubStrButton, "clicked", G_CALLBACK( FindSubstr ), NULL );
    gtk_grid_attach( GTK_GRID( grid ), findSubStrButton, 2, 0, 1, 1 );

    findSubSeqButton = gtk_button_new_with_label( "Find if subsequence" );
    g_signal_connect( findSubSeqButton, "clicked", G_CALLBACK( FindSubsequences ), NULL );
    gtk_grid_attach( GTK_GRID( grid ), findSubSeqButton, 2, 1, 1, 1 );

    gtk_widget_show_all( window );
    gtk_main();

    return 0;
}