// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef UITESTSERVER_H
#define UITESTSERVER_H

#include <Spix/TestServer.h>

#include <atomic>
#include <gtest/gtest.h>

class UITestServer;
static UITestServer* srv;

class UITestServer : public spix::TestServer {
public:
	UITestServer(int _argc, char* _argv[])
		: argc(_argc)
		, argv(_argv)
	{
	}

	int getResult()
	{
		return result.load();
	}

protected:
	int argc;
	char** argv;
	std::atomic<int> result { 0 };

	void executeTest() override
	{
		srv = this;
		::testing::InitGoogleTest(&argc, argv);
		int testResult = RUN_ALL_TESTS();
		result.store(testResult);
	}
};

#endif // UITESTSERVER_H
