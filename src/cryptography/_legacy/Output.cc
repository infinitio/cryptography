#if defined(INFINIT_CRYPTOGRAPHY_LEGACY)
# include <cryptography/_legacy/Output.hh>
# include <cryptography/_legacy/Input.hh>

namespace infinit
{
  namespace cryptography
  {
    /*-------------.
    | Construction |
    `-------------*/

    Output::Output(uint64_t const size):
      _buffer(size)
    {
    }

    Output::Output(elle::Buffer const& buffer):
      _buffer(buffer.contents(), buffer.size())
    {
    }

    Output::Output(elle::Buffer&& buffer):
      _buffer(std::move(buffer))
    {
    }

    Output::Output(Output const& other):
      _buffer(other._buffer.contents(), other._buffer.size())
    {
    }

    Output::Output(Output&& other):
      _buffer(std::move(other._buffer))
    {
    }

    /*----------.
    | Operators |
    `----------*/

    bool
    Output::operator ==(Output const& other) const
    {
      if (this == &other)
        return (true);

      return (this->_buffer == other._buffer);
    }

    bool
    Output::operator <(Output const& other) const
    {
      if (this == &other)
        return (false);

      return (this->_buffer < other._buffer);
    }

    bool
    Output::operator <=(Output const& other) const
    {
      if (this == &other)
        return (true);

      return (this->_buffer <= other._buffer);
    }

    bool
    Output::operator ==(Input const& other) const
    {
      return (elle::ConstWeakBuffer(this->_buffer) == other.buffer());
    }

    bool
    Output::operator <(Input const& other) const
    {
      return (elle::ConstWeakBuffer(this->_buffer) < other.buffer());
    }

    bool
    Output::operator <=(Input const& other) const
    {
      return (elle::ConstWeakBuffer(this->_buffer) <= other.buffer());
    }

    /*----------.
    | Printable |
    `----------*/

    void
    Output::print(std::ostream& stream) const
    {
      stream << this->_buffer;
    }

    /*--------------.
    | Serialization |
    `--------------*/

    Output::Output(elle::serialization::SerializerIn& serializer)
    {
      this->serialize(serializer);
    }

    void
    Output::serialize(elle::serialization::Serializer& serializer)
    {
      serializer.serialize("data", this->_buffer);
    }
  }
}

#else
# warning "LEGACY: this file should not have been included"
#endif
