#include <cryptography/dh/low.hh>
#include <cryptography/cryptography.hh>
#include <cryptography/finally.hh>

#include <elle/log.hh>
#include <elle/Buffer.hh>

#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/engine.h>
#include <openssl/crypto.h>
#include <openssl/err.h>

ELLE_LOG_COMPONENT("infinit.cryptography.dh.low");

namespace infinit
{
  namespace cryptography
  {
    namespace dh
    {
      namespace low
      {
        /*----------.
        | Functions |
        `----------*/

        ::DH*
        DH_priv2pub(::DH* private_key)
        {
          ELLE_TRACE_FUNCTION(private_key);

          ELLE_ASSERT_NEQ(private_key, nullptr);

          // Duplicate the parameters and manually copy the public key.
          //
          // Note that OpenSSL does not provide a better way to do that ;(
          DH* _dh = ::DHparams_dup(private_key);
          _dh->pub_key = BN_dup(private_key->pub_key);

          return (_dh);
        }

        ::DH*
        DH_dup(::DH* key)
        {
          ELLE_TRACE_FUNCTION(key);

          ELLE_ASSERT_NEQ(key, nullptr);

          ::DH_up_ref(key);

          return (key);
        }
      }
    }
  }
}
