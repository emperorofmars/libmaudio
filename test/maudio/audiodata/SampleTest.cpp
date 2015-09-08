/*
 * test of AudioSample
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#include <gtest/gtest.h>
#include "maudio/audiodata/Sample.hpp"
#include <memory>
#include <vector>
#include <iostream>

TEST(Sample, something){
	std::shared_ptr<maudio::ISample> s(new maudio::Sample(std::vector<float>{2, 3}));
	EXPECT_EQ(s->get(0), 2);
	EXPECT_EQ(s->get(1), 3);
	s->set(4, 1);
	EXPECT_EQ(s->get(0), 2);
	EXPECT_EQ(s->get(1), 4);
}

