#include <cryptography/hash.hh>
#include <cryptography/raw.hh>

#include <elle/Buffer.hh>
#include <elle/log.hh>

namespace infinit
{
  namespace cryptography
  {
    /*----------.
    | Functions |
    `----------*/

#if !defined(INFINIT_CRYPTOGRAPHY_LEGACY)
    elle::Buffer
    hash(elle::ConstWeakBuffer const& plain,
         Oneway const oneway)
    {
      elle::IOStream _plain(plain.istreambuf());

      // The cast is required because of the legacy functions.
      return (hash(static_cast<std::istream&>(_plain), oneway));
    }
#endif

    elle::Buffer
    hash(std::istream& plain,
         Oneway const oneway)
    {

      ::EVP_MD const* function = oneway::resolve(oneway);

      return (raw::hash(function, plain));
    }
  }
}
