//
// Created by Lennard on 02.11.22.
//
#include <string>
#include <stdexcept>
#include "../src/HuffmanCoder.h"

// https://bastian.rieck.me/blog/posts/2017/simple_unit_tests/
#define ASSERT_TRUE(condition, msg) {                               \
  if (!(condition)) {                                               \
    throw std::runtime_error(   std::string( __FILE__ )             \
                              + std::string( ":" )                  \
                              + std::to_string( __LINE__ )          \
                              + std::string( " in " )               \
                              + std::string( __PRETTY_FUNCTION__ )  \
                              + std::string(" message: ")           \
                              + (msg)                               \
    );                                                              \
  }                                                                 \
}

#define ASSERT_EQUAL(x, y, msg) {                             \
  if ((x) != (y)) {                                                 \
    throw std::runtime_error(   std::string( __FILE__ )             \
                              + std::string( ":" )                  \
                              + std::to_string( __LINE__ )          \
                              + std::string( " in " )               \
                              + std::string( __PRETTY_FUNCTION__ )  \
                              + std::string( ": " )                 \
                              + std::to_string( ( x ) )             \
                              + std::string( " != " )               \
                              + std::to_string( ( y ) )             \
                              + std::string(" message: ")           \
                              + (msg)                               \
    );                                                              \
  }                                                                 \
}

std::vector<unsigned char > toVector(std::string string) {
    std::vector<unsigned char> vector;
    for (int i = 0; i < string.size(); i++) {
        vector.push_back(string[i]);
    }
    return vector;
}

void testEncodeDecode() {
    auto err = std::make_shared<int>(0);
    auto string = std::string("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Eget nulla facilisi etiam dignissim. Sagittis orci a scelerisque purus. Sem nulla pharetra diam sit amet nisl suscipit adipiscing. Et sollicitudin ac orci phasellus egestas tellus rutrum tellus pellentesque. Fermentum dui faucibus in ornare quam viverra orci sagittis eu. Suscipit tellus mauris a diam maecenas sed. Quam pellentesque nec nam aliquam sem et. Pharetra sit amet aliquam id diam maecenas ultricies. Ultricies mi quis hendrerit dolor magna eget est lorem. Scelerisque felis imperdiet proin fermentum leo vel orci. Varius sit amet mattis vulputate enim nulla aliquet porttitor lacus. Nisi est sit amet facilisis. Enim eu turpis egestas pretium aenean pharetra magna ac. Faucibus a pellentesque sit amet.");
    auto content = toVector(string);
    HuffmanCoder coder(content, err);
    auto encodedContent = coder.encode();
    HuffmanCoder coderDecode(encodedContent->content, err);
    auto decodedText = coderDecode.decode(err);
    ASSERT_TRUE(*err == SUCCESS, "Error was " + std::to_string(*err))
    ASSERT_TRUE(*decodedText == string, "decode encode not the same")
}

void testEncodeDecodeHistogramCorruption() {
    auto err = std::make_shared<int>(0);
    auto string = std::string("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Eget nulla facilisi etiam dignissim. Sagittis orci a scelerisque purus. Sem nulla pharetra diam sit amet nisl suscipit adipiscing. Et sollicitudin ac orci phasellus egestas tellus rutrum tellus pellentesque. Fermentum dui faucibus in ornare quam viverra orci sagittis eu. Suscipit tellus mauris a diam maecenas sed. Quam pellentesque nec nam aliquam sem et. Pharetra sit amet aliquam id diam maecenas ultricies. Ultricies mi quis hendrerit dolor magna eget est lorem. Scelerisque felis imperdiet proin fermentum leo vel orci. Varius sit amet mattis vulputate enim nulla aliquet porttitor lacus. Nisi est sit amet facilisis. Enim eu turpis egestas pretium aenean pharetra magna ac. Faucibus a pellentesque sit amet.");
    auto content = toVector(string);
    HuffmanCoder coder(content, err);
    auto encodedContent = coder.encode();
    encodedContent->content[3] = 7;
    HuffmanCoder coderDecode(encodedContent->content, err);
    auto decodedText = coderDecode.decode(err);
    ASSERT_TRUE(*err == HISTOGRAM_ERROR, "Return code was " + std::to_string(*err))
}

void testEncodeDecodeTextCorruption() {
    auto err = std::make_shared<int>(0);
    auto string = std::string("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Eget nulla facilisi etiam dignissim. Sagittis orci a scelerisque purus. Sem nulla pharetra diam sit amet nisl suscipit adipiscing. Et sollicitudin ac orci phasellus egestas tellus rutrum tellus pellentesque. Fermentum dui faucibus in ornare quam viverra orci sagittis eu. Suscipit tellus mauris a diam maecenas sed. Quam pellentesque nec nam aliquam sem et. Pharetra sit amet aliquam id diam maecenas ultricies. Ultricies mi quis hendrerit dolor magna eget est lorem. Scelerisque felis imperdiet proin fermentum leo vel orci. Varius sit amet mattis vulputate enim nulla aliquet porttitor lacus. Nisi est sit amet facilisis. Enim eu turpis egestas pretium aenean pharetra magna ac. Faucibus a pellentesque sit amet.");
    auto content = toVector(string);
    HuffmanCoder coder(content, err);
    auto encodedContent = coder.encode();
    encodedContent->content[encodedContent->content.size()-3] = 7;
    HuffmanCoder coderDecode(encodedContent->content, err);
    auto decodedText = coderDecode.decode(err);
    ASSERT_TRUE(*err == TEXT_ERROR, "Return code was " + std::to_string(*err))
}

int main(int argc, char *argv[]) {
    testEncodeDecode();
    testEncodeDecodeHistogramCorruption();
    testEncodeDecodeTextCorruption();
    return 0;
}