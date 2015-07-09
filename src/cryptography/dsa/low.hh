#ifndef INFINIT_CRYPTOGRAPHY_DSA_LOW_HH
# define INFINIT_CRYPTOGRAPHY_DSA_LOW_HH

# include <openssl/dsa.h>

namespace infinit
{
  namespace cryptography
  {
    namespace dsa
    {
      namespace low
      {
        /*----------.
        | Functions |
        `----------*/

        /// Return a copy of the given private key that has been transformed
        /// into a DSA public key.
        ::DSA*
        DSA_priv2pub(::DSA* private_key);
        /// Duplicate a DSA key.
        ::DSA*
        DSA_dup(::DSA* key);
      }
    }
  }
}

#endif
