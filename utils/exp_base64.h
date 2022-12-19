#pragma once
#include "base64.h"
#include <string>
#include "stdafx.h"

std::string Base64Encode(const SOUI::IStringA *src) {
	char* buf = new char[BASE64_ENCODE_OUT_SIZE(src->GetLength())+1];
	int len = base64_encode((const unsigned char*)src->c_str(), src->GetLength(), buf);
	std::string ret(buf, len);
	delete[]buf;
	return ret;
}

void Base64Decode(const std::string *src, SOUI::IStringA* out) {
	unsigned char* buf = new unsigned char[BASE64_DECODE_OUT_SIZE(src->length())];
	int len = base64_decode(src->c_str(), src->length(), buf);
	out->Assign2((const char*)buf, len);
	delete[]buf;
}