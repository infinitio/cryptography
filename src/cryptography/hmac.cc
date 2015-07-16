#include <openssl/err.h>

#include <elle/Buffer.hh>
#include <elle/log.hh>

#include <cryptography/hmac.hh>
#include <cryptography/raw.hh>
#include <cryptography/finally.hh>
#include <cryptography/Error.hh>

ELLE_LOG_COMPONENT("infinit.cryptography.hmac");

namespace infinit
{
  namespace cryptography
  {
    namespace hmac
    {
      /*----------.
      | Functions |
      `----------*/

#if !defined(INFINIT_CRYPTOGRAPHY_LEGACY)
      elle::Buffer
      sign(elle::ConstWeakBuffer const& plain,
           elle::String const& key,
           Oneway const oneway)
      {
        ELLE_TRACE_FUNCTION(key, oneway);
        ELLE_DUMP("plain: %x", plain);

        elle::IOStream _plain(plain.istreambuf());

        return (sign(_plain, key, oneway));
      }

      elle::Boolean
      verify(elle::ConstWeakBuffer const& digest,
             elle::ConstWeakBuffer const& plain,
             elle::String const& key,
             Oneway const oneway)
      {
        ELLE_TRACE_FUNCTION(key, oneway);
        ELLE_DUMP("digest: %x", digest);
        ELLE_DUMP("plain: %x", plain);

        elle::IOStream _plain(plain.istreambuf());

        return (verify(digest, _plain, key, oneway));
      }
#endif

      elle::Buffer
      sign(std::istream& plain,
           elle::String const& key,
           Oneway const oneway)
      {
        ELLE_TRACE_FUNCTION(key, oneway);

        ::EVP_MD const* function = oneway::resolve(oneway);

        ::EVP_PKEY *_key = nullptr;

        if ((_key = ::EVP_PKEY_new_mac_key(EVP_PKEY_HMAC,
                                           NULL,
                                           (const unsigned char*)key.data(),
                                           key.size())) == nullptr)
          throw Error(
            elle::sprintf("unable to generate a MAC key: %s",
                          ::ERR_error_string(ERR_get_error(), nullptr)));

        INFINIT_CRYPTOGRAPHY_FINALLY_ACTION_FREE_EVP_PKEY(_key);

        // Apply the HMAC function with the given key.
        elle::Buffer digest = raw::hmac::sign(plain, _key, function);

        ::EVP_PKEY_free(_key);
        INFINIT_CRYPTOGRAPHY_FINALLY_ABORT(_key);

        return (digest);
      }

      elle::Boolean
      verify(elle::ConstWeakBuffer const& digest,
             std::istream& plain,
             elle::String const& key,
             Oneway const oneway)
      {
        ELLE_TRACE_FUNCTION(key, oneway);

        elle::Buffer _digest = sign(plain, key, oneway);

        if (digest.size() != _digest.size())
          return (false);

        // Compare using low-level OpenSSL functions to prevent timing attacks.
        if (CRYPTO_memcmp(digest.contents(),
                          _digest.contents(),
                          _digest.size()) != 0)
          return (false);

        return (true);

      }
    }
  }
}
