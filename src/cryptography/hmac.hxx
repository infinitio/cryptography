#ifndef INFINIT_CRYPTOGRAPHY_HMAC_HXX
# define INFINIT_CRYPTOGRAPHY_HMAC_HXX

# include <utility>

# include <openssl/evp.h>
# include <openssl/err.h>
# include <openssl/hmac.h>

# include <elle/Buffer.hh>
# include <elle/log.hh>

# include <cryptography/raw.hh>
# include <cryptography/finally.hh>

namespace infinit
{
  namespace cryptography
  {
    namespace hmac
    {
      /*----------.
      | Functions |
      `----------*/

      template <typename K>
      elle::Buffer
      sign(elle::ConstWeakBuffer const& plain,
           K const& key,
           Oneway const oneway)
      {
        elle::IOStream _plain(plain.istreambuf());
        return (sign(_plain, key, oneway));
      }

      template <typename K>
      bool
      verify(elle::ConstWeakBuffer const& digest,
             elle::ConstWeakBuffer const& plain,
             K const& key,
             Oneway const oneway)
      {
        elle::IOStream _plain(plain.istreambuf());
        return (verify(digest, _plain, key, oneway));
      }

      template <typename K>
      elle::Buffer
      sign(std::istream& plain,
           K const& key,
           Oneway const oneway)
      {
        ::EVP_MD const* function = oneway::resolve(oneway);

        // Apply the HMAC function with the given key.
        elle::Buffer digest =
          raw::hmac::sign(key.key().get(), function, plain);

        return (digest);
      }

      template <typename K>
      bool
      verify(elle::ConstWeakBuffer const& digest,
             std::istream& plain,
             K const& key,
             Oneway const oneway)
      {
        ::EVP_MD const* function = oneway::resolve(oneway);

        return (raw::hmac::verify(key.key().get(),
                                  function,
                                  digest,
                                  plain));
      }
    }
  }
}

#endif
