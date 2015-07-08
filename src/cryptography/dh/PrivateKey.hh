#ifndef INFINIT_CRYPTOGRAPHY_DH_PRIVATEKEY_HH
# define INFINIT_CRYPTOGRAPHY_DH_PRIVATEKEY_HH

# include <cryptography/fwd.hh>
# include <cryptography/types.hh>
# include <cryptography/SecretKey.hh>
# include <cryptography/Oneway.hh>
# include <cryptography/Cipher.hh>
# include <cryptography/dh/fwd.hh>

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
      /// Represent a private key in the DH asymmetric cryptosystem.
      class PrivateKey:
        public elle::Printable
      {
        /*-------------.
        | Construction |
        `-------------*/
      public:
        /// Construct a private key based on the given EVP_PKEY key whose
        /// ownership is transferred.
        explicit
        PrivateKey(::EVP_PKEY* key);
        /// Construct a private key based on the given DH key whose
        /// ownership is transferred to the private key.
        explicit
        PrivateKey(::DH* dh);
        PrivateKey(PrivateKey const& other);
        PrivateKey(PrivateKey&& other);
        virtual
        ~PrivateKey() = default;

        /*--------.
        | Methods |
        `--------*/
      private:
        /// Construct the object based on the given DH structure whose
        /// ownership is transferred to the callee.
        void
        _construct(::DH* dh);
        /// Prepare the private key cryptographic contexts.
        void
        _prepare();
        /// Check that the key is valid.
        void
        _check() const;
      public:
        /// Compute a shared session secret key based on the peer's public
        /// key.
        SecretKey
        agree(PublicKey const& peer_K) const;
        /// Return the private key's size in bytes.
        elle::Natural32
        size() const;
        /// Return the private key's length in bits.
        elle::Natural32
        length() const;

        /*----------.
        | Operators |
        `----------*/
      public:
        elle::Boolean
        operator ==(PrivateKey const& other) const;
        ELLE_OPERATOR_NO_ASSIGNMENT(PrivateKey);

        /*----------.
        | Printable |
        `----------*/
      public:
        void
        print(std::ostream& stream) const override;

        /*-----------.
        | Attributes |
        `-----------*/
      private:
        ELLE_ATTRIBUTE_R(types::EVP_PKEY, key);
        ELLE_ATTRIBUTE_R(Oneway, digest_algorithm);
        // Note that the contexts are not serialized because they can
        // be reconstructed out of the paddings and algorithms above.
        struct
        {
          types::EVP_PKEY_CTX agree;
        } _context;
      };
    }
  }
}

# include <cryptography/dh/PrivateKey.hxx>

#endif
