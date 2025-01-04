#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ), data_(capacity) {}

bool Writer::is_closed() const
{
  return finished_;
}

void Writer::push( string data )
{
  auto insert_num = std::min(capacity_ - num_, data.size());
  for ( size_t i = 0; i != insert_num; ++i ) {
    data_[( i + pos_ + num_ ) % capacity_] = data[i];
  }
  num_ += insert_num;
  push_num_ += insert_num;
}

void Writer::close()
{
  finished_ = true;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - num_;
}

uint64_t Writer::bytes_pushed() const
{
  return push_num_;
}

bool Reader::is_finished() const
{
  return num_ == 0 && finished_;
}

uint64_t Reader::bytes_popped() const
{
  return pop_num_;
}

string_view Reader::peek() const
{
  return { (data_.data() + pos_), 1 };
}

void Reader::pop( uint64_t len )
{
  auto remove_num = std::min(num_, len);
  pos_ = ( pos_ + remove_num ) % capacity_;
  num_ -= remove_num;
  pop_num_ += remove_num;
}

uint64_t Reader::bytes_buffered() const
{
  return num_;
}
