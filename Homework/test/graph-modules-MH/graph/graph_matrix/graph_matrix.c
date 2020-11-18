//       $Id: graph_matrix.c 2653 2020-11-16 17:34:07Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/se/sw/swo3/trunk/Aufgaben/WS16/VZ/src/graph-modules-MH/graph/graph_matrix/graph_matrix.c $
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

#include "./graph_matrix.h"

#include <assert.h>
#include <stdio.h>

void graph_matrix_some_function (graph_matrix * p_graph) {
   assert (p_graph != NULL);

   printf ("function 'void graph_matrix_some_function (graph_matrix *)' called\n");
}

void graph_matrix_some_other_function (graph_matrix * p_graph) {
   assert (p_graph != NULL);

   printf ("function 'void graph_matrix_some_other_function (graph_matrix *)' called\n");
}
