#include "stdafx.h"



TEST(FactoryMethod, testMakeAnimalHorse)
{
	Animal *a = Animal::make_animal(Animal::AnimalTypes::Horse);

	Horse *h = dynamic_cast<Horse *>(a);

	EXPECT_NE(nullptr, h);

	delete a;
}

TEST(FactoryMethod, testMakeAnimalDog)
{
	Animal *a = Animal::make_animal(Animal::AnimalTypes::Dog);

	Dog *h = dynamic_cast<Dog *>(a);

	EXPECT_NE(nullptr, h);

	delete a;
}

TEST(FactoryMethod, testMakeAnimalCat)
{
	Animal *a = Animal::make_animal(Animal::AnimalTypes::Cat);

	Cat *h = dynamic_cast<Cat *>(a);

	EXPECT_NE(nullptr, h);

	delete a;
}

TEST(FactoryMethod, horseWhines)
{
	Animal *a = Animal::make_animal(Animal::AnimalTypes::Horse);

	testing::internal::CaptureStdout();

	a->make_a_noise();

	EXPECT_EQ("Horse whines\n", testing::internal::GetCapturedStdout());
}

TEST(FactoryMethod, dogBarks)
{
	Animal *a = Animal::make_animal(Animal::AnimalTypes::Dog);

	testing::internal::CaptureStdout();

	a->make_a_noise();

	EXPECT_EQ("Dog barks\n", testing::internal::GetCapturedStdout());
}

TEST(FactoryMethod, catMews)
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
