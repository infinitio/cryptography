#ifndef INFINIT_CRYPTOGRAPHY_RSA_PRIVATEKEY_HH
# define INFINIT_CRYPTOGRAPHY_RSA_PRIVATEKEY_HH

# include <utility>

# include <openssl/evp.h>

# include <elle/serialization.hh>
# if defined(INFINIT_CRYPTOGRAPHY_LEGACY)
#  include <elle/serialize/construct.hh>
#  include <elle/concept/Uniquable.hh>
# endif

ELLE_OPERATOR_RELATIONALS();

# include <cryptography/fwd.hh>
# include <cryptography/types.hh>
# include <cryptography/Oneway.hh>
# include <cryptography/Cipher.hh>
# include <cryptography/rsa/Seed.hh>
# include <cryptography/rsa/Padding.hh>
# include <cryptography/rsa/defaults.hh>

//
// ---------- Class -----------------------------------------------------------
//

namespace infinit
{
  namespace cryptography
  {
    namespace rsa
    {
      /// Represent a private key in the RSA asymmetric cryptosystem.
      class PrivateKey:
        public elle::Printable
# if defined(INFINIT_CRYPTOGRAPHY_LEGACY)
        , public elle::serialize::DynamicFormat<PrivateKey>
        , public elle::concept::MakeUniquable<PrivateKey>
# endif
      {
        /*-------------.
        | Construction |
        `-------------*/
      public:
        /// Construct a private key based on the given EVP_PKEY key whose
        /// ownership is transferred.
        explicit
        PrivateKey(::EVP_PKEY* key
# if defined(INFINIT_CRYPTOGRAPHY_LEGACY)
                   , Padding const encryption_padding =
                     defaults::encryption_padding
                   , Padding const signature_padding =
                     defaults::signature_padding
                   , Oneway const oneway =
                     defaults::oneway
                   , Cipher const envelope_cipher =
                     defaults::envelope_cipher
                   , Mode const envelope_mode =
                     defaults::envelope_mode
# endif
                  );
        /// Construct a private key based on the given RSA key whose
        /// ownership is transferred to the private key.
        explicit
        PrivateKey(::RSA* rsa
# if defined(INFINIT_CRYPTOGRAPHY_LEGACY)
                   , Padding const encryption_padding =
                     defaults::encryption_padding
                   , Padding const signature_padding =
                     defaults::signature_padding
                   , Oneway const oneway =
                     defaults::oneway
                   , Cipher const envelope_cipher =
                     defaults::envelope_cipher
                   , Mode const envelope_mode =
                     defaults::envelope_mode
# endif
                  );
        PrivateKey(PrivateKey const& other);
        PrivateKey(PrivateKey&& other);
        virtual
        ~PrivateKey() = default;

        /*--------.
        | Methods |
        `--------*/
      private:
        /// Construct the object based on the given RSA structure whose
        /// ownership is transferred to the callee.
        void
        _construct(::RSA* rsa);
        /// Check that the key is valid.
        void
        _check() const;
      public:
# if !defined(INFINIT_CRYPTOGRAPHY_LEGACY)
        /// Open the envelope and return the original plain text.
        elle::Buffer
        open(elle::ConstWeakBuffer const& code,
             Cipher const cipher = defaults::envelope_cipher,
             Mode const mode = defaults::envelope_mode) const;
        /// Open the envelope, decrypt its stream-based content and return the
        /// original plan text in the output stream.
        void
        open(std::istream& code,
             std::ostream& plain,
             Cipher const cipher = defaults::envelope_cipher,
             Mode const mode = defaults::envelope_mode) const;
        /// Decrypt a code with the raw public key.
        ///
        /// WARNING: This method cannot be used to decrypt large amount of
        ///          data as constrained by the key's modulus. Please refer
        ///          to the seal()/open() methods.
        elle::Buffer
        decrypt(elle::ConstWeakBuffer const& code,
                Padding const padding = defaults::encryption_padding) const;
        /// Sign the given plain text and return the signature.
        elle::Buffer
        sign(elle::ConstWeakBuffer const& plain,
             Padding const padding = defaults::signature_padding,
             Oneway const oneway = defaults::oneway) const;
# endif
        /// Write the signature in the output stream given the stream-based
        /// plain text.
        elle::Buffer
        sign(std::istream& plain,
             Padding const padding = defaults::signature_padding,
             Oneway const oneway = defaults::oneway) const;
        /// Return the private key's size in bytes.
        elle::Natural32
        size() const;
        /// Return the private key's length in bits.
        elle::Natural32
        length() const;

# if defined(INFINIT_CRYPTOGRAPHY_ROTATION)
        /*---------.
        | Rotation |
        `---------*/
      public:
        /// Construct a private key based on a given seed i.e in a deterministic
        /// way.
        explicit
        PrivateKey(Seed const& seed);
        /// Return the seed once rotated by the private key.
        Seed
        rotate(Seed const& seed) const;
# endif

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

        /*-------------.
        | Serializable |
        `-------------*/
      public:
        PrivateKey(elle::serialization::SerializerIn& serializer);
        void
        serialize(elle::serialization::Serializer& serializer);
        typedef elle::serialization_tag serialization_tag;

        /*-----------.
        | Attributes |
        `-----------*/
      private:
        ELLE_ATTRIBUTE_R(types::EVP_PKEY, key);

# if defined(INFINIT_CRYPTOGRAPHY_LEGACY)
        /*-------.
        | Legacy |
        `-------*/
      public:
        // construction
        PrivateKey() {}
        ELLE_SERIALIZE_CONSTRUCT_DECLARE(PrivateKey)
        {}
        // methods
        template <typename T = Clear>
        T
        decrypt(Code const& code) const;
        template <typename T = Plain>
        Signature
        sign(T const& value) const;
        // serializable
        ELLE_SERIALIZE_FRIEND_FOR(PrivateKey);
        using elle::serialize::SerializableMixin<
          infinit::cryptography::rsa::PrivateKey,
          elle::serialize::Base64Archive>::serialize;
        // attributes
        ELLE_ATTRIBUTE_R(Padding, encryption_padding);
        ELLE_ATTRIBUTE_R(Padding, signature_padding);
        ELLE_ATTRIBUTE_R(Oneway, oneway);
        ELLE_ATTRIBUTE_R(Cipher, envelope_cipher);
        ELLE_ATTRIBUTE_R(Mode, envelope_mode);
        ELLE_ATTRIBUTE_R(elle::Natural16, legacy_format);
# endif
      };
    }
  }
}

//
// ---------- DER -------------------------------------------------------------
//

namespace infinit
{
  namespace cryptography
  {
    namespace rsa
    {
      namespace privatekey
      {
        namespace der
        {
          /*----------.
          | Functions |
          `----------*/

          /// Encode the private key in DER.
          elle::Buffer
          encode(PrivateKey const& K);
          /// Decode the private key from a DER representation.
          PrivateKey
          decode(elle::ConstWeakBuffer const& buffer);
        }
      }
    }
  }
}

# include <cryptography/rsa/PrivateKey.hxx>

#endif
