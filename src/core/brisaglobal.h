/*
2 	* Universidade Federal de Campina Grande
3 	* Centro de Engenharia Elétrica e Informática
4 	* Laboratório de Sistemas Embarcados e Computação Pervasiva
5 	* BRisa / BRisa-Qt
6 	* Filename: brisaconfig.cpp
7 	* Created:
8 	* Description: Define Some Macros to use with BRisa code.
9 	* Authors: Andre Dieb Martins <andre.dieb@gmail.com> @since 2009
10 	*
11 	*
12 	* Copyright (C) <2009> <Embbeded Systems and Pervasive Computing Laboratory>
13 	*
14 	* BRisa-Qt is free software: you can redistribute it and/or modify
15 	* it under the terms of the GNU Lesser General Public License as
16 	* published by the Free Software Foundation, either version 3 of
17 	* the License, or (at your option) any later version.
18 	*
19 	* This program is distributed in the hope that it will be useful,
20 	* but WITHOUT ANY WARRANTY; without even the implied warranty of
21 	* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
22 	* GNU General Public License for more details.
23 	*
24 	* You should have received a copy of the GNU Lesser General Public License
25 	* along with this program. If not, see <http://www.gnu.org/licenses/>.
26 	*
27 	*/

#ifndef _BRISAGLOBAL
#define _BRISAGLOBAL
#define BRISA_VERSION 0x000001
#define BRISA_VERSION_STR "0.1"

#if defined BUILD_BRISA_CORE
# define BRISA_CORE_EXPORT Q_DECL_EXPORT
#else
# define BRISA_CORE_EXPORT Q_DECL_IMPORT
#endif

#if defined BUILD_BRISA_UTILS
# define BRISA_UTILS_EXPORT Q_DECL_EXPORT
#else
# define BRISA_UTILS_EXPORT Q_DECL_IMPORT
#endif

#ifdef BRISA_UPNP_EXPORT
#undef BRISA_UPNP_EXPORT
#endif

#if defined BUILD_BRISA_UPNP
# define BRISA_UPNP_EXPORT Q_DECL_EXPORT
#else
# define BRISA_UPNP_EXPORT Q_DECL_IMPORT
#endif

#if defined BUILD_BRISA_CORE || defined BUILD_BRISA_UTILS || defined BUILD_BRISA_UPNP
# define BUILD_BRISA
#endif

#endif /* _BRISAGLOBAL */
