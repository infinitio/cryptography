#ifndef INFINIT_CRYPTOGRAPHY_HASH_HH
# define INFINIT_CRYPTOGRAPHY_HASH_HH

# include <cryptography/fwd.hh>
# include <cryptography/Oneway.hh>
# include <cryptography/Digest.hh>

# include <elle/types.hh>

# include <openssl/evp.h>

# include <iosfwd>

namespace infinit
{
  namespace cryptography
  {
    /*----------.
    | Functions |
    `----------*/

    /// Hash anything serializable and return a digest.
    template <typename T>
    Digest
    hash(T const& value,
         Oneway oneway);
  }
}

# include <cryptography/hash.hxx>

#endif
