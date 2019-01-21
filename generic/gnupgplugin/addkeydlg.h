/*
 * addkeydlg.h - generating key pair dialog
 *
 * Copyright (C) 2013  Ivan Romanov <drizt@land.ru>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.     See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef ADDKEYDLG_H
#define ADDKEYDLG_H

#include <QDialog>
#include <QDate>

namespace Ui { class AddKeyDlg; }

class AddKeyDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AddKeyDlg(QWidget *parent = 0);
    ~AddKeyDlg();

    QString name() const;
    QString email() const;
    QString comment() const;
    int type() const;
    int length() const;
    QDate expiration() const;
    QString pass() const;

private slots:
    void checkPass();
    void fillLenght(const QString &type);

private:
    Ui::AddKeyDlg *ui;
};

#endif // ADDKEYDLG_H
