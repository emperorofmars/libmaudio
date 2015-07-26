/*
 * test of AudioSample
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#include "MaudioTest.hpp"

#include "core/audiodata/Sample.hpp"

TEST(Sample, something){
	maudio::Sample *s = new maudio::Sample(std::vector<float>{2, 3});
	EXPECT_EQ((*s)[0], 2);
	EXPECT_EQ((*s)[1], 3);
	s->set(1, 4);
	EXPECT_EQ((*s)[0], 2);
	EXPECT_EQ((*s)[1], 4);
}

