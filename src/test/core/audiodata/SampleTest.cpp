/*
 * test of AudioSample
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#include "test/MaudioTest.hpp"

#include "core/audiodata/Sample.hpp"

TEST(Sample, something){
	maudio::ISample *s = new maudio::Sample(std::vector<float>{2, 3});
	EXPECT_EQ((*s)[0], 2);
	EXPECT_EQ((*s)[1], 3);
	s->set(4, 1);
	EXPECT_EQ((*s)[0], 2);
	EXPECT_EQ((*s)[1], 4);
}

