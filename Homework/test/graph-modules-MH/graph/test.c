//       $Id: test.c 2653 2020-11-16 17:34:07Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/se/sw/swo3/trunk/Aufgaben/WS16/VZ/src/graph-modules-MH/graph/test.c $
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

// -----------------------------------------------------------------------------

// #define USE_GRAPH_LIST     // Either define USE_GRAPH_LIST or USE_GRAPH_MATRIX
   #define USE_GRAPH_MATRIX   // here in the source or via the compiler option -D.

#include "./graph_selector.h"

// -----------------------------------------------------------------------------

#include <stdlib.h>

int main () {
   graph_t graph = {0};

   graph_some_function (&graph);
   graph_some_other_function (&graph);

   return EXIT_SUCCESS;
}
