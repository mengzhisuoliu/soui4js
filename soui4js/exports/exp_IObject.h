#pragma once
#include <interface/SObject-i.h>

void Exp_IObject(qjsbind::Module* module)
{
	JsClass<IObject> jsCls = module->ExportClass<IObject>("IObject");
	jsCls.Init(JsClass<IObjRef>::class_id());
	jsCls.AddFunc("IsClass", &IObject::IsClass);
	jsCls.AddFunc("GetObjectClass", &IObject::GetObjectClass);
	jsCls.AddFunc("GetObjectType", &IObject::GetObjectType);

	jsCls.AddFunc("GetID", &IObject::GetID);
	jsCls.AddFunc("SetID", &IObject::SetID);
	jsCls.AddFunc("GetName", &IObject::GetNameA);
	jsCls.AddFunc("SetName", &IObject::SetName);

	jsCls.AddFunc("InitFromXml", &IObject::InitFromXml);
	jsCls.AddFunc("ISetAttribute", &IObject::ISetAttribute);
	jsCls.AddFunc("SetAttribute", &IObject::SetAttributeA);
	jsCls.AddFunc("GetAttribute", &IObject::GetAttribute);
	jsCls.AddFunc("SetAttrHandler", &IObject::SetAttrHandler);
}
