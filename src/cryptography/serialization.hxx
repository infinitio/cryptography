#ifndef INFINIT_CRYPTOGRAPHY_SERIALIZATION_HXX
# define INFINIT_CRYPTOGRAPHY_SERIALIZATION_HXX

namespace infinit
{
  namespace cryptography
  {
    /*----------.
    | Functions |
    `----------*/

    template <typename S>
    void
    serialize(elle::serialization::Serializer& serializer,
              typename S::Type*& data)
    {
      if (serializer.out())
      {
        ELLE_ASSERT_NEQ(data, nullptr);
        elle::Buffer representation = S::encode(data);
        serializer.serialize(S::identifier, representation);
      }
      else
      {
        elle::Buffer representation;
        serializer.serialize(S::identifier, representation);
        ELLE_ASSERT_EQ(data, nullptr);
        data = S::decode(representation);
      }
    }
  }
}

#endif
