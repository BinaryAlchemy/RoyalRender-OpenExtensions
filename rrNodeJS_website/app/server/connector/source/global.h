// data.h
#ifndef __NODE_GLOBAL__
#define __NODE_GLOBAL__

#include <node.h>
#include <node_object_wrap.h>
#include <v8.h>


class RRGlobal : public node::ObjectWrap
{
public:
	// construction!
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void newInst(const v8::FunctionCallbackInfo<v8::Value>& args);

	RRGlobal(void);
	~RRGlobal(void);

	// misc
	static bool objectIs(v8::Handle<v8::Object> obj);

	// ---- init
	static void init(void);

private:
	static v8::Persistent<v8::Function> constructor;
};


#endif