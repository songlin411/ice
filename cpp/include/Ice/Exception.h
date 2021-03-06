// **********************************************************************
//
// Copyright (c) 2003-2016 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_EXCEPTION_H
#define ICE_EXCEPTION_H

#include <IceUtil/Exception.h>
#include <Ice/Config.h>
#include <Ice/Format.h>
#include <Ice/Handle.h>
#include <Ice/ObjectF.h>
#include <Ice/ValueF.h>

namespace IceInternal
{

namespace Ex
{

ICE_API void throwUOE(const ::std::string&, const ::Ice::ValuePtr&);
ICE_API void throwMemoryLimitException(const char*, int, size_t, size_t);
ICE_API void throwMarshalException(const char*, int, const std::string&);

}

}

namespace Ice
{

class OutputStream;
class InputStream;

typedef IceUtil::Exception Exception;

class ICE_API LocalException : public IceUtil::Exception
{
public:

    LocalException(const char*, int);

#ifdef ICE_CPP11_COMPILER
    virtual ~LocalException();
#else
    virtual ~LocalException() throw();
#endif

    static const std::string& ice_staticId();

#ifndef ICE_CPP11_MAPPING
    virtual LocalException* ice_clone() const = 0;
#endif
};

class ICE_API UserException : public IceUtil::Exception
{
public:

    static const std::string& ice_staticId();

    virtual void __write(::Ice::OutputStream*) const;
    virtual void __read(::Ice::InputStream*);

    virtual bool __usesClasses() const;

#ifndef ICE_CPP11_MAPPING
    virtual UserException* ice_clone() const = 0;
#endif

protected:

    virtual void __writeImpl(::Ice::OutputStream*) const {};
    virtual void __readImpl(::Ice::InputStream*) {};
};

class ICE_API SystemException : public IceUtil::Exception
{
public:

    SystemException(const char*, int);
#ifdef ICE_CPP11_COMPILER
    virtual ~SystemException();
#else
    virtual ~SystemException() throw();
#endif

    static const std::string& ice_staticId();

#ifndef ICE_CPP11_MAPPING
    virtual SystemException* ice_clone() const = 0;
#endif

};

}

#endif
