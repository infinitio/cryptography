#include <Python.h>
#include <boost/python.hpp>

#include <elle/serialization/json.hh>

#include <cryptography/rsa/PublicKey.hh>
#include <cryptography/hash.hh>

using namespace boost::python;
namespace crypto = infinit::cryptography;

#pragma GCC diagnostic ignored "-Wmissing-declarations"

struct buffer_python_converter
{
  static
  PyObject*
  convert(elle::Buffer const& b)
  {
    auto res = PyBytes_FromStringAndSize(
      reinterpret_cast<char const*>(b.mutable_contents()), b.size());
    const_cast<elle::Buffer&>(b).release();
    return res;
    // return boost::python::incref(
    //   boost::python::object(
    //     s.toLatin1().constData()).ptr());
  }

  static
  void*
  convertible(PyObject* object)
  {
    return PyBytes_Check(object) ? object : nullptr;
  }

  static
  void
  construct(
    PyObject* object,
    boost::python::converter::rvalue_from_python_stage1_data* data)
  {
    auto contents = PyBytes_AsString(object);
    auto size = PyBytes_Size(object);
    void* storage = (
      (boost::python::converter::rvalue_from_python_storage<elle::ConstWeakBuffer>*)
      data)->storage.bytes;
    new (storage) elle::ConstWeakBuffer(contents, size);
    data->convertible = storage;
  }
};

struct PublicKey
  : public crypto::rsa::PublicKey
{
  PublicKey(std::string const& s)
    : PublicKey(std::stringstream(s))
  {}

  // FIXME: implement python deserializer
  PublicKey(std::stringstream const& input)
    : crypto::rsa::PublicKey(
      elle::serialization::json::deserialize<crypto::rsa::PublicKey>
      (const_cast<std::stringstream&>(input)))
  {}
};

elle::Buffer
hash(elle::ConstWeakBuffer input)
{
  return crypto::hash(input, crypto::Oneway::sha256);
}

BOOST_PYTHON_MODULE(cryptography)
{
  class_<PublicKey>("PublicKey", init<std::string>())
    ;

  def("hash", &hash);

  elle::Buffer empty;

  boost::python::to_python_converter<
    elle::Buffer,
    buffer_python_converter>();
  boost::python::converter::registry::push_back(
    &buffer_python_converter::convertible,
    &buffer_python_converter::construct,
    boost::python::type_id<elle::ConstWeakBuffer>());
}
