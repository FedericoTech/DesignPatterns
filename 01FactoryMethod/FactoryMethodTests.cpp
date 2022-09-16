#include <iostream>

#include "FactoryMethod.hpp"
#include <gtest/gtest.h>


TEST(FactoryMethod, createHorse)
{
	Animal *a = Animal::make_animal(Animal::AnimalTypes::Horse);

	testing::internal::CaptureStdout();

	a->make_a_noise();

	EXPECT_EQ("Horse whines\n", testing::internal::GetCapturedStdout());
}

TEST(FactoryMethod, createDog)
{
	Animal *a = Animal::make_animal(Animal::AnimalTypes::Dog);

	testing::internal::CaptureStdout();

	a->make_a_noise();

	EXPECT_EQ("Dog barks\n", testing::internal::GetCapturedStdout());
}

TEST(FactoryMethod, createCat)
{
	Animal *a = Animal::make_animal(Animal::AnimalTypes::Cat);

	testing::internal::CaptureStdout();

	a->make_a_noise();

	EXPECT_EQ("Cat mews\n", testing::internal::GetCapturedStdout());
}



int main(int argc, char **argv) {
      ::testing::InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
}
