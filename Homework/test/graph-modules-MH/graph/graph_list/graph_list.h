//       $Id: graph_list.h 2653 2020-11-16 17:34:07Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/se/sw/swo3/trunk/Aufgaben/WS16/VZ/src/graph-modules-MH/graph/graph_list/graph_list.h $
// $Revision: 2653 $
//     $Date: 2020-11-16 18:34:07 +0100 (Mo., 16 Nov 2020) $
//   $Author: p20068 $
//   Creator: Peter Kulczycki
//  Creation: November 16, 2020
// Copyright: (c) 2020 Peter Kulczycki (peter.kulczycki<AT>fh-hagenberg.at)
//   License: This document contains proprietary information belonging to
//            University of Applied Sciences Upper Austria, Campus Hagenberg.
//            It is distributed under the Boost Software License (see
//            https://www.boost.org/users/license.html).

#if !defined GRAPH_LIST_H
#define      GRAPH_LIST_H

typedef struct graph_list {
   int some_data;
} graph_list;

void graph_list_some_function       (graph_list *);
void graph_list_some_other_function (graph_list *);

#endif   // GRAPH_LIST_H
