
#include <gtest/gtest.h>

int foo(){
	return 4;
}

TEST(example, footest){
	EXPECT_EQ(4, foo());
}

int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}