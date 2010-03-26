/* brisa-c++
 *
 * Copyright (C) 2009 Andre Dieb Martins <andre.dieb@gmail.com>
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
