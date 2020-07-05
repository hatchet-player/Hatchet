/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2012, Christopher Reichert <creichert07@gmail.com>
 *   Copyright 2012, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *
 *   Hatchet is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Hatchet is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Hatchet. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef METADATAEDITOR_H
#define METADATAEDITOR_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>

#include "ui_MetadataEditor.h"
#include "Query.h"
#include "Result.h"
#include "Typedefs.h"

class QString;

class MetadataEditor : public QDialog
{
Q_OBJECT

public:
    MetadataEditor( const Hatchet::query_ptr& query, const Hatchet::playlistinterface_ptr& plInterface, QWidget* parent = 0 );
    MetadataEditor( const Hatchet::result_ptr& result, const Hatchet::playlistinterface_ptr& plInterface, QWidget* parent = 0 );
    ~MetadataEditor() {};

    void init( const Hatchet::playlistinterface_ptr& plInterface );

protected:
    QString title() const { return ui->titleLineEdit->text(); }
    QString artist() const { return ui->artistLineEdit->text(); }
    QString album() const { return ui->albumLineEdit->text(); }
    int albumPos() const { return ui->albumPosSpinBox->value(); }
    int year() const { return ui->yearSpinBox->value(); }
    int bitrate() const { return ui->bitrateSpinBox->value(); }

    void loadResult( const Hatchet::result_ptr& result );
    void loadQuery( const Hatchet::query_ptr& query );

private slots:
    void writeMetadata( bool closeDlg = false );
    void enablePushButtons();
    void loadNextQuery();
    void loadPreviousQuery();

    /* tag attributes */
    void setTitle( const QString& title );
    void setArtist( const QString& artist );
    void setAlbum( const QString& album );
    void setAlbumPos( unsigned int num );
    void setDuration( unsigned int duration );
    void setYear( int year );
    void setBitrate( unsigned int num );

    /* file attributes */
    void setFileName( const QString& fn );
    void setFileSize( const QString& size );

    void setEditable( bool editable );

private:
    void setWindowTitle( const QString& title );

    Ui::MetadataEditor* ui;

    Hatchet::result_ptr m_result;
    Hatchet::query_ptr m_query;

    Hatchet::playlistinterface_ptr m_interface;
    QStringList m_editFiles;

    qint64 m_index;
    bool m_editable;
};

#endif // METADATAEDITOR_H
