#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
//#include ".\nlohmann\json.hpp"
#include "nlohmann\json.hpp"

// this testing project is using nlohmann::jason
// its github is https://github.com/nlohmann/json

void TestWriteAlgorithmJsonFileByObject()
{
	nlohmann::json TextBox = { "TextBox", {{"RangeMin", 0}, {"RangeMax", 1000}, {"ValueType", "int"} } };
	
	nlohmann::json testObj;
	testObj["pi"] = 3.1415926;
	testObj["test"]["obj"] = 42;
	testObj["array"] = {1, 2, 3};

	nlohmann::json jw;
	jw["Period Algorithm"] = { {"object", {TextBox}}, {"array", TextBox}}; // Test putting object and array to json file.
	jw["test other method"] = { testObj };

	auto temp = jw.dump();
	std::ofstream o("../Bin/TestJsonFile2.json");
	//o << std::setw(4) << temp << std::endl;
	o << temp << std::endl;
}

void TestWriteAlgorithmJsonFileDirectly()
{
	// object use "{{" and "}}" to include.
	// array use "{" and "}" to include.
	nlohmann::json jw = {
		{"Period Algorithm",
		 {
			 {"Period", {
				 {"TextBox", {
					 {"RangeMin", 0}, {"RangeMax", 1000}, {"ValueType", "int"}
				 }}
			 }},
			 {"Direction", {
				{"ComboBox", {
						{"verticle", {
							{"picture",nullptr}
						}},
						{"horizontal", {
							{"picture",nullptr}
						}}
				}}
			 }},
			 {"Peek",{
				 {"SliderBar", {
					 {"RangeMin", -100000}, {"RangeMax", 100000}, {"Step", 1}
				 }}
			 }}
		 }
		}
	};
	auto temp = jw.dump();
	std::ofstream o("TestJsonFile.json");
	//o << std::setw(4) << temp << std::endl;
	o << temp << std::endl;
}

std::string makeRecieveCmd()
{
	nlohmann::json rec;
	rec["CMD"] = "InspectionAll";

	// inspection data
	nlohmann::json inspData;
	inspData["WinNum"] = 3;
	// test array
	inspData["ROI"] = {
		{ {"No", 1}, {"x", 10}, {"y", 10}, {"width", 200}, {"height", 300}, {"AlgorithmName", "PeriodAlgorithm"}, {"Period", 10}, {"slice", 1000} },
		{ {"No", 2}, {"x", 10}, {"y", 10}, {"width", 200}, {"height", 60}, {"AlgorithmName", "SealInspection" }, {"Gray", -30}, {"Width", 30}, {"RangeUpper", 40}, {"RangeLower", 20} },
		{ {"No", 3}, {"x", 40}, {"y", 5}, {"width", 50}, {"height", 50}, {"AlgorithmName", "SealShift" }, {"Gray", -30}, {"ShiftUpper", 100}, {"ShiftLower", 50} }
	};

	rec["data"] = { inspData };

	//std::cout << rec << std::endl;
	//auto temp = rec.dump();
	//std::ofstream file("../Bin/RecieveCmd.json");
	//file << temp << std::endl;

	return rec.dump();
}

void TestReadJson(char* Command)
{
	std::string inputStr = std::string(Command);
	try {
		nlohmann::json j_test = nlohmann::json::parse(inputStr);
		std::cout << "\n\nrecieve command parse:" << std::endl;
		std::cout << "Command: " << j_test["CMD"] << std::endl;
		int winNum = j_test["data"]["WinNum"];
		std::cout << "Data-Window num: " << winNum << std::endl;
		std::cout << "Data-Window ROI array: " << j_test["data"]["ROI"] << std::endl;

		std::cout << "\nEach ROI information:" << std::endl;
		//for (int i = 0; i < winNum; i++) {
		//	std::cout << i + 1 << "-th ROI:\n\t" << j_test["data"]["ROI"][i] << std::endl;
		//}
		// test using other nlohmann::json to catch input json
		// it would be applying to Algorithm reading input arguments.
		nlohmann::json j_sub = j_test["data"]["ROI"];
		for (int i = 0; i < winNum; i++) {
			std::cout << i + 1 << "-th ROI:\n\t" << j_sub[i] << std::endl;
		}

		std::string tempStr = j_test["data"]["ROI"].dump().c_str();
		std::cout << "\ntest convert nlohmann::jason to std::string:\n" << tempStr << std::endl;
		nlohmann::json j_sub_test2 = nlohmann::json::parse(tempStr);
		for (int i = 0; i < winNum; i++) {
			std::cout << i + 1 << "-th ROI:\n\t" << j_sub_test2[i] << std::endl;
		}

	}
	catch (std::exception ex) {
		std::cout << "When read recieve json have problem: " << ex.what() << std::endl;
	}
	catch (...) {
		std::cout << "When read recieve json have other problem" << std::endl;
	}
}

void TestMakeSendPackage()
{
	try {
		// ROI1 result
		nlohmann::json Roi1;
		Roi1["No"] = 1;
		Roi1["message"] = "success";
		Roi1["data"] = {
			{"num", 3},
			{"InspectResult",{
					{{"Type", "particle"}, {"center_x", 16}, {"center_y", 11}, {"width", 10}, {"height", 10}, {"size", 100}, {"Picture", "192.168.0.11\\DefectImage\\Particle\\1.bmp"}},
					{{"Type", "particle"}, {"center_x", 27}, {"center_y", 11}, {"width", 10}, {"height", 10}, {"size", 100}, {"Picture", "192.168.0.11\\DefectImage\\Particle\\2.bmp"}},
					{{"Type", "particle"}, {"center_x", 38}, {"center_y", 11}, {"width", 10}, {"height", 10}, {"size", 100}, {"Picture", "192.168.0.11\\DefectImage\\Particle\\3.bmp"}},
				}
			}
		};
		//std::cout << "\n\ntest:" << Roi1 << std::endl;

		// ROI2 result
		nlohmann::json Roi2_result;
		Roi2_result["num"] = 3;
		Roi2_result["InspectResult"] = {
			{{"Type", "SealInsp"}, {"center_x", 16}, {"center_y", 11}, {"width", 10}, {"height", 10}, {"SealDefectType", "Fat"}, {"Picture", "192.168.0.11\\DefectImage\\Seal\\1.bmp"}},
			{{"Type", "SealInsp"}, {"center_x", 27}, {"center_y", 11}, {"width", 10}, {"height", 10}, {"SealDefectType", "Thin"}, {"Picture", "192.168.0.11\\DefectImage\\Seal\\2.bmp"}},
			{{"Type", "SealInsp"}, {"center_x", 38}, {"center_y", 11}, {"width", 10}, {"height", 10}, {"SealDefectType", "Broken"}, {"Picture", "192.168.0.11\\DefectImage\\Seal\\3.bmp"}},
		};
		nlohmann::json Roi2;
		Roi2["No"] = 2;
		Roi2["message"] = "success";
		Roi2["data"] = {Roi2_result};

		// ROI3 result
		nlohmann::json Roi3;
		Roi3["No"] = 3;
		Roi3["message"] = "fail";
		Roi3["data"] = "not found seal!";

		// integrate sub json
		nlohmann::json RoiResultJson;
		RoiResultJson = {Roi1, Roi2, Roi3};

		// send package json
		nlohmann::json send;
		send["CMD"] = "inspectionAll";
		send["Result"] = RoiResultJson;

		std::string temp = send.dump();
		std::cout << "\n\nSend data length = " << temp.length() << std::endl;
		//auto temp = send.dump();
		//std::ofstream file("../Bin/result.json");
		//file << temp << std::endl;
	}
	catch (std::exception ex) {
	}
	catch (nlohmann::json::error_handler_t ex) {
	}
	catch (...) {
	}
}

void main()
{
	std::ifstream file;
	file.open("../Bin/AlgorithmSetting.json");

	std::stringstream strStream;
	strStream << file.rdbuf();
	std::string str = strStream.str();
	//debug
	//std::cout << str << std::endl;

	//TestWriteAlgorithmJsonFileByObject();
	//TestWriteAlgorithmJsonFileDirectly();

	std::string jsonStr = makeRecieveCmd();
	std::cout << "package string length: " << jsonStr.length() << std::endl;
	TestReadJson((char*)(jsonStr.c_str()));

	TestMakeSendPackage();

	system("pause");
}