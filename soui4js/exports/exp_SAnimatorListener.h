#pragma once
#include <interface/SValueAnimator-i.h>

class SAnimatorListener : public IAnimatorListener, public qjsbind::JsThisOwner
{
public:
	SAnimatorListener() {}

public:
	STDMETHOD_(void, onAnimationStart)(THIS_ IValueAnimator* pAnimator) {
		if (!m_onAnimationStart.IsObject())
			return;
		qjsbind::Context& ctx = *m_onAnimationStart.context();
		qjsbind::Value args[] = {
			NewValue(ctx, pAnimator)
		};
		ctx.Call(GetJsThis(), m_onAnimationStart, ARRAYSIZE(args), args);
	}
	STDMETHOD_(void, onAnimationEnd)(THIS_ IValueAnimator* pAnimator) {
		if (!m_onAnimationEnd.IsObject())
			return;
		qjsbind::Context& ctx = *m_onAnimationEnd.context();
		qjsbind::Value args[] = {
			NewValue(ctx, pAnimator)
		};
		ctx.Call(GetJsThis(), m_onAnimationEnd, ARRAYSIZE(args), args);

	}
	STDMETHOD_(void, onAnimationRepeat)(THIS_ IValueAnimator* pAnimator) {
		if (!m_onAnimationRepeat.IsObject())
			return;
		qjsbind::Context& ctx = *m_onAnimationRepeat.context();
		qjsbind::Value args[] = {
			NewValue(ctx, pAnimator)
		};
		ctx.Call(GetJsThis(), m_onAnimationRepeat, ARRAYSIZE(args), args);
	}

public:
	const WeakValue& GetJsThis() const override {
		if (m_cbHandler.IsObject())
			return m_cbHandler;
		else
			return JsThisOwner::GetJsThis();
	}
public:
	static void Mark(SAnimatorListener* pThis, JS_MarkFunc* mark_fun) {
		pThis->m_onAnimationStart.Mark(mark_fun);
		pThis->m_onAnimationEnd.Mark(mark_fun);
		pThis->m_onAnimationRepeat.Mark(mark_fun);
		pThis->m_cbHandler.Mark(mark_fun);
	}

	Value m_onAnimationStart;
	Value m_onAnimationEnd;
	Value m_onAnimationRepeat;

	Value m_cbHandler;
};

class SAnimatorUpdateListener : public IAnimatorUpdateListener, public qjsbind::JsThisOwner
{
public:
	SAnimatorUpdateListener() {}

public:
	STDMETHOD_(void, onAnimationUpdate)(THIS_ IValueAnimator* pAnimator) {
		if (!m_onAnimationUpdate.IsObject())
			return;
		qjsbind::Context& ctx = *m_onAnimationUpdate.context();
		qjsbind::Value args[] = {
			NewValue(ctx, pAnimator)
		};
		ctx.Call(GetJsThis(), m_onAnimationUpdate, ARRAYSIZE(args), args);
	}

public:
	const WeakValue& GetJsThis() const override {
		if (m_cbHandler.IsObject())
			return m_cbHandler;
		else
			return JsThisOwner::GetJsThis();
	}
public:
	static void Mark(SAnimatorUpdateListener* pThis, JS_MarkFunc* mark_fun) {
		pThis->m_onAnimationUpdate.Mark(mark_fun);
		pThis->m_cbHandler.Mark(mark_fun);
	}

	Value m_onAnimationUpdate;
	Value m_cbHandler;
};

void Exp_SAnimatorListener(qjsbind::Module* module) {
	JsClass<SAnimatorListener > jsCls = module->ExportClass<SAnimatorListener>("SAnimatorListener");
	jsCls.Init<SAnimatorListener::Mark>();
	jsCls.AddCtor<constructor<SAnimatorListener>>();
	jsCls.AddGetSet("cbHandler", &SAnimatorListener::m_cbHandler);
	jsCls.AddGetSet("onAnimationStart", &SAnimatorListener::m_onAnimationStart);
	jsCls.AddGetSet("onAnimationEnd", &SAnimatorListener::m_onAnimationEnd);
	jsCls.AddGetSet("onAnimationRepeat", &SAnimatorListener::m_onAnimationRepeat);
}

void Exp_SAnimatorUpdateListener(qjsbind::Module* module) {
	JsClass<SAnimatorUpdateListener > jsCls = module->ExportClass<SAnimatorUpdateListener>("SAnimatorUpdateListener");
	jsCls.Init<SAnimatorUpdateListener::Mark>();
	jsCls.AddCtor<constructor<SAnimatorUpdateListener>>();
	jsCls.AddGetSet("cbHandler", &SAnimatorUpdateListener::m_cbHandler);
	jsCls.AddGetSet("onAnimationUpdate", &SAnimatorUpdateListener::m_onAnimationUpdate);
}