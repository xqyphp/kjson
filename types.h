/***************************************************************************
 *            types.h
 *
 *  Tue January 05 02:28:49 2016
 *  Copyright  2016  lk
 *  <user@host>
 ****************************************************************************/
/*
 * types.h
 *
 * Copyright (C) 2016 - lk
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

#define LOG(...) printf(__VA_ARGS__)

#ifndef NULL
#define NULL ((void*)0)
#endif


typedef unsigned char bool_t;

#define K_TRUE  	1
#define K_FALSE     0

#define K_SUCCESS   0
#define K_ERROR    -1


typedef struct pool_s pool_t;
typedef struct list_s list_t;


#endif
