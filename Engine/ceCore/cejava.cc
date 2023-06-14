
#include <ceCore/cejava.hh>

namespace ce::java
{

JNIEnv* Env::s_env = nullptr;

Env::Env()
{

}


JNIEnv* Env::Get()
{
  return s_env;
}

void Env::Set(JNIEnv* env)
{
  s_env = env;
}



}