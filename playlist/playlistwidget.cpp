#include "playlistwidget.h"



/*
 * TODO:
 * - Fix columns size
 * - more columns, like rating
 */


PlaylistWidget::PlaylistWidget()
{
    setColumnCount(4);


    // Define titles for labels
    QStringList playlistWidgetHeaders;
    playlistWidgetHeaders.append("Title");
    playlistWidgetHeaders.append("Artist");
    playlistWidgetHeaders.append("Album");
    playlistWidgetHeaders.append("Duration");
    setHeaderLabels(playlistWidgetHeaders);

    // Set alignment for the columns' headers
    QHeaderView *headers = header();
    headers->setDefaultAlignment(Qt::AlignCenter);
    headers->setSortIndicatorShown(true);



}
