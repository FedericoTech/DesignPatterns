
#include "stdafx.h"

class AbstractFactoryTests : public ::testing::Test {
public:
	AbstractFactoryTests(){
		linuxFactory = new LinuxFactory;
		windowsFactory = new WindowsFactory;
	}

	~AbstractFactoryTests(){
		delete linuxFactory;
		delete windowsFactory;
	}

protected:
	Factory *linuxFactory;
	Factory *windowsFactory;
};


TEST_F(AbstractFactoryTests, linuxCreateButton)
{
	Widget *w = linuxFactory->create_button();

	LinuxButton *wb = dynamic_cast<LinuxButton *>(w);

	EXPECT_NE(nullptr, wb);
}

TEST_F(AbstractFactoryTests, linuxCreateMenu)
{
	Widget *w = linuxFactory->create_menu();

	LinuxMenu *wm = dynamic_cast<LinuxMenu *>(w);

	EXPECT_NE(nullptr, wm);
}

TEST_F(AbstractFactoryTests, windowsCreateButton)
{
	Widget *w = windowsFactory->create_button();

	WindowsButton *wb = dynamic_cast<WindowsButton *>(w);

	EXPECT_NE(nullptr, wb);
}

TEST_F(AbstractFactoryTests, windowsCreateMenu)
{
	Widget *w = windowsFactory->create_menu();

	WindowsMenu *wm = dynamic_cast<WindowsMenu *>(w);

	EXPECT_NE(nullptr, wm);
}

TEST_F(AbstractFactoryTests, testLinuxButton)
{
	Widget *w = linuxFactory->create_button();

	testing::internal::CaptureStdout();

	w->draw();

	EXPECT_EQ("LinuxButton\n", testing::internal::GetCapturedStdout());
}

TEST_F(AbstractFactoryTests, testLinuxeMenu)
{
	Widget *w = linuxFactory->create_menu();

	testing::internal::CaptureStdout();

	w->draw();

	EXPECT_EQ("LinuxMenu\n", testing::internal::GetCapturedStdout());
}

TEST_F(AbstractFactoryTests, testWindowsButton)
{
	Widget *w = windowsFactory->create_button();

	testing::internal::CaptureStdout();

	w->draw();

	EXPECT_EQ("WindowsButton\n", testing::internal::GetCapturedStdout());
}

TEST_F(AbstractFactoryTests, testWindowsMenu)
{
	Widget *w = windowsFactory->create_menu();

	testing::internal::CaptureStdout();

	w->draw();

	EXPECT_EQ("WindowsMenu\n", testing::internal::GetCapturedStdout());
}

TEST(ClientTests, clientOnLinux)
{
	std::unique_ptr<Factory> factory = std::make_unique<LinuxFactory>();

	Client c(std::move(factory));

	testing::internal::CaptureStdout();

	c.draw();

	EXPECT_EQ(
		"LinuxButton\nLinuxButton\nLinuxMenu\nLinuxButton\nLinuxMenu\n",
		testing::internal::GetCapturedStdout()
	);
}

TEST(ClientTests, clientOnWindows)
{
	std::unique_ptr<Factory> factory = std::make_unique<WindowsFactory>();

	Client c(std::move(factory));

	testing::internal::CaptureStdout();

	c.draw();

	EXPECT_EQ(
		"WindowsButton\nWindowsButton\nWindowsMenu\nWindowsButton\nWindowsMenu\n",
		testing::internal::GetCapturedStdout()
	);
}

int main(int argc, char **argv) {
      ::testing::InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
}
