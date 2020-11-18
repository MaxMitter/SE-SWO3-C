//       $Id: graph_matrix.h 2653 2020-11-16 17:34:07Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/se/sw/swo3/trunk/Aufgaben/WS16/VZ/src/graph-modules-MH/graph/graph_matrix/graph_matrix.h $
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

#if !defined GRAPH_MATRIX_H
#define      GRAPH_MATRIX_H

typedef struct graph_matrix {
   int some_data;
} graph_matrix;

void graph_matrix_some_function       (graph_matrix *);
void graph_matrix_some_other_function (graph_matrix *);

#endif   // GRAPH_MATRIX_H
