#ifndef INFINIT_CRYPTOGRAPHY_DH_PUBLICKEY_HH
# define INFINIT_CRYPTOGRAPHY_DH_PUBLICKEY_HH

# include <cryptography/dh/PrivateKey.hh>
# include <cryptography/fwd.hh>
# include <cryptography/types.hh>
# include <cryptography/Oneway.hh>
# include <cryptography/Cipher.hh>

# include <elle/types.hh>
# include <elle/attribute.hh>
# include <elle/operator.hh>

# include <utility>
ELLE_OPERATOR_RELATIONALS();

# include <openssl/evp.h>

//
// ---------- Class -----------------------------------------------------------
//

namespace infinit
{
  namespace cryptography
  {
    namespace dh
    {
      /// Represent a public key in the DH asymmetric cryptosystem.
      class PublicKey:
        public elle::Printable
      {
        /*-------------.
        | Construction |
        `-------------*/
      public:
        /// Construct a public key out of its private counterpart.
        explicit
        PublicKey(PrivateKey const& k);
        /// Construct a public key based on the given EVP_PKEY key whose
        /// ownership is transferred.
        explicit
        PublicKey(::EVP_PKEY* key);
        /// Construct a public key based on the given DH key whose
        /// ownership is transferred to the public key.
        explicit
        PublicKey(::DH* dh);
        PublicKey(PublicKey const& other);
        PublicKey(PublicKey&& other);
        virtual
        ~PublicKey() = default;

        /*--------.
        | Methods |
        `--------*/
      private:
        /// Construct the object based on the given DH structure whose
        /// ownership is transferred to the callee.
        void
        _construct(::DH* dh);
        /// Check that the key is valid.
        void
        _check() const;
      public:
        /// Return the public key's size in bytes.
        uint32_t
        size() const;
        /// Return the public key's length in bits.
        uint32_t
        length() const;

        /*----------.
        | Operators |
        `----------*/
      public:
        elle::Boolean
        operator ==(PublicKey const& other) const;
        ELLE_OPERATOR_NO_ASSIGNMENT(PublicKey);

        /*----------.
        | Printable |
        `----------*/
      public:
        void
        print(std::ostream& stream) const override;

        /*-----------.
        | Attributes |
        `-----------*/
      public:
        ELLE_ATTRIBUTE_R(types::EVP_PKEY, key);
      };
    }
  }
}

# include <cryptography/dh/PublicKey.hxx>

#endif
