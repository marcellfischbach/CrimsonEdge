
#pragma once

#include <cstdint>
#include <csCore/csDefs.hh>

#ifdef CS_JAVA

#include <jni.h>

#endif

//
// Meta information for CS_CLASS definitions
//  Virtual - Prevent the csMOC from implementing CreateInstance

#define CS_CLASS(...)
#define CS_SUPER(Cls) Cls
#define CS_PROPERTY(...)
#define CS_FUNCTION(...)
#ifdef CS_JAVA
#define CS_CLASS_GEN public: \
    const cryo::csClass *GetClass () const override; \
    static const cryo::csClass *GetStaticClass (); \
    void *QueryClass(const cryo::csClass *clazz) override; \
    const void *QueryClass(const cryo::csClass *clazz) const override; \
    jobject CreateJObject () const
#else
#define CS_CLASS_GEN public: \
    const cryo::csClass *GetClass () const override; \
    static const cryo::csClass *GetStaticClass (); \
    void *QueryClass(const cryo::csClass *clazz) override; \
    const void *QueryClass(const cryo::csClass *clazz) const override;
#endif

#ifdef CS_JAVA
#define CS_CLASS_GEN_OBJECT \
    CS_CLASS_GEN; \
    void AddRef() override \
    { \
      m_refCount++; \
    } \
    void Release() override  \
    { \
      --m_refCount; \
      if (m_refCount <= 0) \
      {                     \
        if (m_jobject)        \
        {                     \
          cryo::csJava::Get()->DeleteGlobalRef(m_jobject);          \
          m_jobject = nullptr; \
        }                   \
        delete this;\
      } \
    } \
    CS_NODISCARD int64_t RefCount () const override \
    { \
      return m_refCount; \
    }                       \
    void SetJObject(jobject object) const override \
    {                       \
      m_jobject = object; \
    }                       \
    CS_NODISCARD jobject GetJObject() const override\
    {                       \
      if (!m_jobject && !m_jobjectChecked)       \
      {                     \
        m_jobject = CreateJObject();                \
        m_jobjectChecked = true; \
      }                     \
      return m_jobject;\
    }                       \
private: \
      int64_t m_refCount = 1; \
      mutable bool m_jobjectChecked = false; \
      mutable jobject m_jobject = nullptr


#define CS_DECLARE_JAVA(fqcn) \
private: \
      mutable bool m_jobjectChecked = false; \
      mutable jobject m_jobject = nullptr; \
public:                                \
    CS_NODISCARD jobject GetJObject() const\
    {                       \
      if (!m_jobject && !m_jobjectChecked)       \
      {                                \
          static jclass cls = cryo::csJava::Get() ? cryo::csJava::Get()->FindClass (fqcn) : nullptr; \
          if (cls) \
          { \
            static jmethodID ctor = cryo::csJava::Get()->GetMethodID(cls, "<init>", "(J)V"); \
            if (ctor) \
            { \
              jobject obj = cryo::csJava::Get()->NewObject(cls, ctor, reinterpret_cast<jlong>(this)); \
              if (obj) \
              { \
                m_jobject = cryo::csJava::Get()->NewGlobalRef(obj);                              \
                if (!m_jobject)        \
                {                      \
                  return nullptr;\
                }\
              } \
            } \
          } \
        m_jobjectChecked = true; \
      }                     \
      return m_jobject; \
    }

#else
#define CS_CLASS_GEN_OBJECT \
    CS_CLASS_GEN; \
    void AddRef() override \
    { \
      m_refCount++; \
    } \
    void Release() override  \
    { \
      --m_refCount; \
      if (m_refCount <= 0) \
      { \
          delete this;\
      } \
    } \
    CS_NODISCARD int64_t RefCount () const override \
    { \
      return m_refCount; \
    } \
    private: \
      int64_t m_refCount = 1

#define CS_DECLARE_JAVA(fqcn)

#endif

#define CS_CLASS_GEN_CONSTR m_refCount = 1

#define CS_WEAK_OBJECT(Super) \
  public: void AddRef () { Super::AddRef (); }\
          void Release () { Super::Release (); }


#define CS_SET(oo, no) if (no) no->AddRef(); if (oo) oo->Release(); oo = no
#define CS_ADDREF(o) if (o) o->AddRef()
#define CS_RELEASE(o) if (o) o->Release()

#include <map>
#include <set>
#include <string>
#include <vector>
#include <stdarg.h>
#include <csCore/csCoreExport.hh>
#include <exception>

namespace cryo
{


class csBadMethodInvokation : public std::exception
{
public:
  csBadMethodInvokation(const std::string &msg)
      : m_msg(msg)
  {
  }
  virtual ~csBadMethodInvokation()
  {

  }

  const char *getMessage() const
  {
    return m_msg.c_str();
  }
private:
  std::string m_msg;
};


class csNoSuchMethodException : public std::exception
{
public:
  csNoSuchMethodException(const std::string &methodName)
      : m_methodName(methodName)
  {
  }
  virtual ~csNoSuchMethodException()
  {

  }

  const char *getMethodName() const
  {
    return m_methodName.c_str();
  }
private:
  std::string m_methodName;
};


class csInstantiationException : public std::exception
{
public:
  csInstantiationException(const std::string &className)
      : m_className(className)
  {
  }
  virtual ~csInstantiationException()
  {

  }

  const char *GetClassName() const
  {
    return m_className.c_str();
  }
private:
  std::string m_className;
};


class csClass;

struct CS_CORE_API iObject
{
  iObject() = default;
  virtual ~iObject() = default;
  CS_NODISCARD virtual const csClass *GetClass() const;
  static const csClass *GetStaticClass();

  virtual void AddRef() = 0;

  virtual void Release() = 0;

  CS_NODISCARD virtual int64_t RefCount() const = 0;

#ifdef CS_JAVA
  virtual void SetJObject(jobject object) const = 0;
  CS_NODISCARD virtual jobject GetJObject() const = 0;
#endif

  template<typename T>
  CS_NODISCARD T *Query()
  {
    return reinterpret_cast<T *>(QueryClass(T::GetStaticClass()));
  }

  CS_NODISCARD virtual void *QueryClass(const csClass *clazz);

  template<typename T>
  CS_NODISCARD const T *Query() const
  {
    return reinterpret_cast<const T *>(QueryClass(T::GetStaticClass()));
  }
  CS_NODISCARD virtual const void *QueryClass(const csClass *clazz) const;

  template<typename T>
  bool IsInstanceOf() const;

};


class csAutoRelease
{
private:
  iObject *obj;
public:
  explicit csAutoRelease(iObject *obj) : obj(obj)
  {}
  ~csAutoRelease()
  { CS_RELEASE(obj); }

};


template<typename T>
T *csQueryClass(cryo::iObject *object)
{
  if (!object)
  {
    return 0;
  }
  return reinterpret_cast<T *>(object->QueryClass(T::GetStaticClass()));
}

template<typename T>
const T *csQueryClass(const cryo::iObject *object)
{
  if (!object)
  {
    return 0;
  }
  return reinterpret_cast<const T *>(object->QueryClass(T::GetStaticClass()));
}

enum eConstness
{
  eC_NonConst,
  eC_Const,
  e_FORCE32 = 0xffffffff
};

enum eValueMemoryMode
{
  eVMM_Value,
  eVMM_Reference,
  eVMM_Pointer,
  eVMM_PointerToPointer,
};

enum eFunctionVirtuality
{
  eFV_NonVirtual,
  eFV_Virtual,
};


class CS_CORE_API csValueDeclaration
{
public:
  csValueDeclaration(eConstness constness = eC_NonConst,
                     const std::string &type = "void",
                     eValueMemoryMode mode = eVMM_Value);

  eConstness GetConstness() const;
  const std::string &GetType() const;
  eValueMemoryMode GetMode() const;

  bool operator==(const csValueDeclaration &other) const;
private:
  eConstness       m_constness;
  std::string      m_type;
  eValueMemoryMode m_mode;
};

class CS_CORE_API csProperty
{
public:
  virtual ~csProperty();

  const csValueDeclaration &GetContainerDecl() const;
  const csValueDeclaration &GetDecl() const;
  bool IsContainer() const;
  const std::string &GetName() const;

  template<typename T>
  void Set(cryo::iObject *object, T &t) const
  {
    const void *const_value = reinterpret_cast<const void *>(&t);
    SetValue(object, const_cast<void *>(const_value));
  }


  template<typename T>
  T Get(cryo::iObject *object) const
  {
    void *data = GetValue(object);
    return *reinterpret_cast<T *>(data);
  }

  template<typename T>
  T Get(const cryo::iObject *object) const
  {
    const void *data = GetValue(object);
    return *reinterpret_cast<const T *>(data);
  }


  std::set<std::string> GetProperties() const;
  bool HasProperty(const std::string &property) const;
  std::string GetProperty(const std::string &property) const;


protected:
  csProperty(const csValueDeclaration &containerDecl, const std::string &name, const csValueDeclaration &decl);

  void SetProperty(const std::string &key, const std::string &value = "");
  virtual void SetValue(cryo::iObject *object, void *data) const = 0;
  virtual const void *GetValue(const cryo::iObject *object) const = 0;
  virtual void *GetValue(cryo::iObject *object) const = 0;


private:
  std::string                        m_name;
  csValueDeclaration                 m_containerDecl;
  csValueDeclaration                 m_decl;
  std::map<std::string, std::string> m_properties;

};


class CS_CORE_API csFunctionAttribute
{
public:
  csFunctionAttribute(const csValueDeclaration &type = csValueDeclaration(), const std::string &name = "");

  const csValueDeclaration &GetType() const;
  const std::string &GetName() const;

private:
  csValueDeclaration m_type;
  std::string        m_name;
};

class CS_CORE_API csFunction
{
public:
  virtual ~csFunction()
  {}
  const std::string &GetName() const;
  const csValueDeclaration &GetReturnType() const;
  eFunctionVirtuality GetVirtuality() const;
  eConstness GetConstness() const;

  size_t GetNumberOfAttributes() const;
  const csFunctionAttribute &GetAttribute(size_t idx) const;


  //
  // Invoke void 
  template<typename ... Type>
  void InvokeVoid(cryo::iObject *obj, Type ... args) const
  { InvokeVoidImpl(obj, &args...); }
  template<typename ... Type>
  void InvokeVoid(const cryo::iObject *obj, Type ... args) const
  { InvokeVoidImpl(obj, &args...); }


  //
  // Invoke value
  template<typename R, typename ... Type>
  R InvokeValue(cryo::iObject *obj, Type ... args) const
  {
    R r;
    InvokeValueImpl(obj, &args...);
    return r;
  }
  template<typename R, typename ... Type>
  R InvokeValue(const cryo::iObject *obj, Type ... args) const
  {
    R r;
    InvokeValueImpl(obj, &args...);
    return r;
  }


  //
  // Invoke reference 
  template<typename R, typename ... Types>
  R &InvokeReference(cryo::iObject *obj, Types ... args) const
  { return *reinterpret_cast<R *>(InvokeReferenceImpl(obj, &args...)); }
  template<typename R, typename ... Types>
  R &InvokeReference(const cryo::iObject *obj, Types ... args) const
  { return *reinterpret_cast<R *>(InvokeReferenceImpl(obj, &args...)); }

  //
  // Invoke const-reference 
  template<typename R, typename ... Types>
  const R &InvokeConstReference(cryo::iObject *obj, Types ... args) const
  { return *reinterpret_cast<const R *>(InvokeConstReferenceImpl(obj, &args...)); }
  template<typename R, typename ... Types>
  const R &InvokeConstReference(const cryo::iObject *obj, Types ... args) const
  { return *reinterpret_cast<const R *>(InvokeConstReferenceImpl(obj, &args...)); }


  //
  // Invoke pointer 
  template<typename R, typename ... Types>
  R *InvokePointer(cryo::iObject *obj, Types ... args) const
  { return reinterpret_cast<R *>(InvokePointerImpl(obj, &args...)); }
  template<typename R, typename ... Types>
  R *InvokePointer(const cryo::iObject *obj, Types ... args) const
  { return reinterpret_cast<R *>(InvokePointerImpl(obj, &args...)); }

  //
  // Invoke const-pointer 
  template<typename R, typename ... Types>
  const R *InvokeConstPointer(cryo::iObject *obj, Types ... args) const
  { return reinterpret_cast<const R *>(InvokeConstPointerImpl(obj, &args...)); }
  template<typename R, typename ... Types>
  const R *InvokeConstPointer(const cryo::iObject *obj, Types ... args) const
  { return reinterpret_cast<const R *>(InvokeConstPointerImpl(obj, &args...)); }


protected:
  csFunction(eFunctionVirtuality virtuality,
             const csValueDeclaration &returnType,
             const std::string &name,
             eConstness constness);

  void AddAttribute(const csFunctionAttribute &attribute);

  virtual void InvokeVoidImpl(cryo::iObject *obj, ...) const = 0;
  virtual void InvokeVoidImpl(const cryo::iObject *obj, ...) const = 0;
  virtual void InvokeValueImpl(cryo::iObject *obj, ...) const = 0;
  virtual void InvokeValueImpl(const cryo::iObject *obj, ...) const = 0;
  virtual void *InvokeReferenceImpl(cryo::iObject *obj, ...) const = 0;
  virtual void *InvokeReferenceImpl(const cryo::iObject *obj, ...) const = 0;
  virtual const void *InvokeConstReferenceImpl(cryo::iObject *obj, ...) const = 0;
  virtual const void *InvokeConstReferenceImpl(const cryo::iObject *obj, ...) const = 0;
  virtual void *InvokePointerImpl(cryo::iObject *obj, ...) const = 0;
  virtual void *InvokePointerImpl(const cryo::iObject *obj, ...) const = 0;
  virtual const void *InvokeConstPointerImpl(cryo::iObject *obj, ...) const = 0;
  virtual const void *InvokeConstPointerImpl(const cryo::iObject *obj, ...) const = 0;

private:
  eFunctionVirtuality m_virtuality;
  eConstness          m_constness;
  std::string        m_name;
  csValueDeclaration m_returnType;

  std::vector<csFunctionAttribute> m_attributes;
  csFunctionAttribute              m_invalid;
};


class CS_CORE_API csClass
{
public:
  virtual ~csClass();
  virtual cryo::iObject *CreateInstance() const = 0;
  template<typename T>
  T *CreateInstance() const
  {
    cryo::iObject *obj = CreateInstance();
    if (!obj)
    {
      return 0;
    }

    T *t = cryo::csQueryClass<T>(obj);
    if (!t)
    {
      obj->Release();
      obj = nullptr;
    }
    return t;
  }

  size_t GetNumberOfProperties() const;
  const csProperty *GetProperty(size_t idx) const;
  const csProperty *GetProperty(const std::string &propName) const;

  size_t GetNumberOfFunctions() const;
  const csFunction *GetFunction(size_t idx) const;
  std::vector<const csFunction *> GetFunction(const std::string &functionName) const;
  std::vector<const csFunction *> GetFunction(const std::string &functionName, eConstness constness) const;
  const csFunction *GetFirstFunction(const std::string &functionName) const;
  const csFunction *GetFirstFunction(const std::string &functionName, eConstness constness) const;

  size_t GetNumberOfSuperClasses() const;
  const csClass *GetSuperClass(size_t idx) const;

  bool HasMeta(const std::string &meta) const;
  const std::string GetMeta(const std::string &meta) const;

  const std::string &GetName() const;

  template<typename T>
  bool IsInstanceOf() const
  {
    return IsInstanceOf(T::GetStaticClass());
  }
  bool IsInstanceOf(const csClass *clazz) const;

  template<typename T>
  bool IsAssignableFrom() const
  {
    return IsAssignableFrom(T::GetStaticClass());
  }
  bool IsAssignableFrom(const csClass *clazz) const;


protected:
  csClass(const std::string &name);

  void AddSuperClass(const csClass *parentClass);
  void AddProperty(const csProperty *prop);
  void AddFunction(const csFunction *function);
  void AddMeta(const std::string &key, const std::string &value);
private:
  std::string                   m_name;
  std::vector<const csClass *>    m_superClasses;
  std::vector<const csProperty *> m_properties;
  std::vector<const csFunction *> m_functions;
  std::map<std::string, std::string> m_meta;
};

template<typename T>
T *csNewClassInstance(const csClass *clazz)
{
  return reinterpret_cast<T *>(clazz->CreateInstance());
}

template<typename T>
bool csInstanceOf(const iObject *obj)
{
  if (!obj)
  {
    return false;
  }
  return obj->GetClass()->IsInstanceOf<T>();
}


class CS_CORE_API iObjectClass : public csClass
{
public:
  iObjectClass();

  static iObjectClass *Get();

  virtual cryo::iObject *CreateInstance() const;

};


template<typename T>
bool iObject::IsInstanceOf() const
{
  return GetClass()->IsInstanceOf<T>();
}

#ifdef CS_JAVA

}

#include <csCore/csJava.hh>

namespace cryo
{
#endif

CS_CLASS()
class CS_CORE_API csObject : public CS_SUPER(iObject)
{
CS_CLASS_GEN_OBJECT;

public:
  csObject();
  ~csObject() override;


};


}
