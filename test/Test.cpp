//
// Created by Lennard on 02.11.22.
//
#include <string>
#include <stdexcept>

// https://bastian.rieck.me/blog/posts/2017/simple_unit_tests/
#define ASSERT_TRUE( condition ) {                                                                   \
  if ( !( condition ) ) {                                           \
    throw std::runtime_error(   std::string( __FILE__ )             \
                              + std::string( ":" )                  \
                              + std::to_string( __LINE__ )          \
                              + std::string( " in " )               \
                              + std::string( __PRETTY_FUNCTION__ )  \
    );                                                              \
  }                                                                 \
}

#define ALEPH_ASSERT_EQUAL( x, y ) {                                \
  if ( ( x ) != ( y ) ) {                                           \
    throw std::runtime_error(   std::string( __FILE__ )             \
                              + std::string( ":" )                  \
                              + std::to_string( __LINE__ )          \
                              + std::string( " in " )               \
                              + std::string( __PRETTY_FUNCTION__ )  \
                              + std::string( ": " )                 \
                              + std::to_string( ( x ) )             \
                              + std::string( " != " )               \
                              + std::to_string( ( y ) )             \
    );                                                              \
  }                                                                 \
}

int main(int argc, char *argv[]) {
    ASSERT_TRUE(false)
    return 0;
}
