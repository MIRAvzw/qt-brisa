/* brisa-c++
 *
 * This file is part of brisa-c++.
 *
 * brisa-c++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * brisa-c++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with brisa-c++.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename:
 * Created:
 * Description:
 * Authors: Name <email> @since 2009
 *
 *
 * Copyright (C) <2009> <Embbeded Systems and Pervasive Computing Laboratory>
 *
 * BRisa-Qt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <QtGlobal>
#include <QTime>
#include <iostream>

#include "brisalog.h"

#define COLOR_DEBUG "\033[32;1m"
#define COLOR_WARN "\033[33;1m"
#define COLOR_CRITICAL "\033[31;1m"
#define COLOR_FATAL "\033[33;1m"
#define COLOR_RESET "\033[0m"

#define LOG_WRITE(OUTPUT, COLOR, LEVEL, MSG) OUTPUT << COLOR << \
                        QTime::currentTime().toString("hhmmsszzz").toStdString() << \
                        " " LEVEL " " << COLOR_RESET << MSG << "\n"

static void brisaMessageWritter(QtMsgType type, const char *msg) {
    switch (type) {
    case QtWarningMsg:
        LOG_WRITE(std::cout, COLOR_WARN, "WARN", msg);
        break;
    case QtCriticalMsg:
        LOG_WRITE(std::cout, COLOR_CRITICAL, "CRIT", msg);
        break;
    case QtFatalMsg:
        LOG_WRITE(std::cout, COLOR_FATAL, "FATAL", msg);
        break;
    case QtDebugMsg:
        LOG_WRITE(std::cout, COLOR_DEBUG, "DEBUG", msg);
        break;
    }
}

void brisaLogInitialize(void) {
    qInstallMsgHandler(brisaMessageWritter);
}
