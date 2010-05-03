/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa / BRisa-Qt
 * Filename: brisaconfig.cpp
 * Created:
 * Description: Define Some Macros to use with BRisa code.
 * Authors: Andre Dieb Martins <andre.dieb@gmail.com> @since 2009
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

#ifndef _BRISAGLOBAL
#define _BRISAGLOBAL

#define BRISA_VERSION 0x000001
#define BRISA_VERSION_STR "0.1"

#if defined BUILD_BRISA_CORE
#    define BRISA_CORE_EXPORT Q_DECL_EXPORT
#else
#    define BRISA_CORE_EXPORT Q_DECL_IMPORT
#endif

#if defined BUILD_BRISA_UTILS
#    define BRISA_UTILS_EXPORT Q_DECL_EXPORT
#else
#    define BRISA_UTILS_EXPORT Q_DECL_IMPORT
#endif

#if defined BUILD_BRISA_UPNP
#    define BRISA_UPNP_EXPORT Q_DECL_EXPORT
#else
#    define BRISA_UPNP_EXPORT Q_DECL_IMPORT
#endif

#if defined BUILD_BRISA_CORE || defined BUILD_BRISA_UTILS || defined BUILD_BRISA_UPNP
#    define BUILD_BRISA
#endif

#endif /* _BRISAGLOBAL */
