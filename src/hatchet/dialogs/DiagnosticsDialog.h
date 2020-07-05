/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2011, Dominik Schmidt <dev@dominik-schmidt.de>
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

#ifndef DIAGNOSTICSDIALOG_H
#define DIAGNOSTICSDIALOG_H

#include "accounts/Account.h"

#include <QDialog>
#include <QMap>


class QLabel;

class SipInfo;

namespace Ui
{
    class DiagnosticsDialog;
}

class DiagnosticsDialog : public QDialog
{
Q_OBJECT

public:
    explicit DiagnosticsDialog( QWidget* parent = 0 );
    ~DiagnosticsDialog() {};

private slots:
    void updateLogView();
    void copyToClipboard();
    void openLogfile();

    QString accountLog( Hatchet::Accounts::Account* );

private:
    Ui::DiagnosticsDialog* ui;
    QString peerLog( const QString& nodeid, const QList<Hatchet::peerinfo_ptr>& peerInfos );
};

#endif // DIAGNOSTICSDIALOG_H
