#pragma once

#include <cstddef>
#include <cstring>

#include "../core_api.hpp"

namespace Leth
{
	template <typename TChar> struct CharTraits
	{
		static size_t Length(const TChar *str)
		{
			if (str == nullptr)
				return 0;

			const TChar *it = str;
			while (*it != TChar{})
				++it;

			return static_cast<size_t>(it - str);
		}

		static void Copy(TChar *dst, const TChar *src, size_t count)
		{
			std::memcpy(dst, src, count * sizeof(TChar));
		}

		static void Move(TChar *dst, const TChar *src, size_t count)
		{
			std::memmove(dst, src, count * sizeof(TChar));
		}

		static int Compare(const TChar *a, const TChar *b, size_t count)
		{
			for (size_t i = 0; i < count; ++i)
			{
				if (a[i] < b[i])
					return -1;
				if (b[i] < a[i])
					return 1;
			}
			return 0;
		}
	};

	template <> struct CharTraits<char>
	{
		static size_t Length(const char *str)
		{
			return str ? std::strlen(str) : 0;
		}
		static void Copy(char *dst, const char *src, size_t count)
		{
			std::memcpy(dst, src, count);
		}
		static void Move(char *dst, const char *src, size_t count)
		{
			std::memmove(dst, src, count);
		}
		static int Compare(const char *a, const char *b, size_t count)
		{
			return count ? std::memcmp(a, b, count) : 0;
		}
	};

	template <typename TChar> class LETH_CORE_API StringBase
	{
	public:
		using Traits = CharTraits<TChar>;
		using ConstIterator = const TChar *;

		static constexpr size_t NPos = static_cast<size_t>(-1);

		constexpr StringBase() = default;
		constexpr StringBase(const TChar *str, size_t size) : _data(str), _size(size)
		{
		}
		StringBase(const TChar *str) : _data(str), _size(Traits::Length(str))
		{
		}

		constexpr const TChar *Data() const
		{
			return _data;
		}
		constexpr size_t Length() const
		{
			return _size;
		}
		constexpr bool Empty() const
		{
			return _size == 0;
		}

		constexpr ConstIterator begin() const
		{
			return _data;
		}
		constexpr ConstIterator end() const
		{
			return _data + _size;
		}

		const TChar &operator[](size_t index) const
		{
			return _data[index];
		}

		int Compare(const StringBase &other) const
		{
			const size_t common = _size < other._size ? _size : other._size;
			const int result = Traits::Compare(_data, other._data, common);
			if (result != 0)
				return result;
			if (_size < other._size)
				return -1;
			if (_size > other._size)
				return 1;
			return 0;
		}

		bool Equals(const StringBase &other) const
		{
			return _size == other._size && Traits::Compare(_data, other._data, _size) == 0;
		}

		bool StartsWith(const StringBase &prefix) const
		{
			return _size >= prefix._size && Traits::Compare(_data, prefix._data, prefix._size) == 0;
		}

		bool EndsWith(const StringBase &suffix) const
		{
			return _size >= suffix._size &&
				   Traits::Compare(_data + (_size - suffix._size), suffix._data, suffix._size) == 0;
		}

		size_t IndexOf(TChar value, size_t from = 0) const
		{
			for (size_t i = from; i < _size; ++i)
				if (_data[i] == value)
					return i;
			return NPos;
		}

		size_t IndexOf(const StringBase &needle, size_t from = 0) const
		{
			if (needle._size == 0)
				return from <= _size ? from : NPos;
			if (needle._size > _size)
				return NPos;

			for (size_t i = from; i + needle._size <= _size; ++i)
				if (Traits::Compare(_data + i, needle._data, needle._size) == 0)
					return i;

			return NPos;
		}

		bool Contains(const StringBase &needle) const
		{
			return IndexOf(needle) != NPos;
		}

		StringBase Substring(size_t start, size_t count = NPos) const
		{
			if (start > _size)
				start = _size;
			const size_t remaining = _size - start;
			return StringBase(_data + start, count < remaining ? count : remaining);
		}

		friend bool operator==(const StringBase &a, const StringBase &b)
		{
			return a.Equals(b);
		}
		friend bool operator!=(const StringBase &a, const StringBase &b)
		{
			return !a.Equals(b);
		}
		friend bool operator<(const StringBase &a, const StringBase &b)
		{
			return a.Compare(b) < 0;
		}

	protected:
		const TChar *_data = nullptr;
		size_t _size = 0;
	};

	template <typename TChar, size_t SSOBufferCapacity = 32>
	class LETH_CORE_API DynamicString : public StringBase<TChar>
	{
		static_assert(SSOBufferCapacity >= 2, "The SSO buffer needs to fit 1 character + termninator");

	public:
		using Base = StringBase<TChar>;
		using Traits = typename Base::Traits;
		using Base::NPos;

		static constexpr size_t SSOCapacity = SSOBufferCapacity - 1;

		DynamicString() noexcept
		{
			ResetToSmall();
		}

		DynamicString(const TChar *str)
		{
			ResetToSmall();
			Assign(str, Traits::Length(str));
		}

		DynamicString(const TChar *str, size_t size)
		{
			ResetToSmall();
			Assign(str, size);
		}

		DynamicString(const Base &view)
		{
			ResetToSmall();
			Assign(view.Data(), view.Length());
		}

		DynamicString(size_t count, TChar value)
		{
			ResetToSmall();
			Resize(count, value);
		}

		DynamicString(const DynamicString &other) : Base()
		{
			ResetToSmall();
			Assign(other.Data(), other.Length());
		}

		DynamicString(DynamicString &&other) noexcept : Base()
		{
			AdoptFrom(other);
		}

		~DynamicString()
		{
			ReleaseHeap();
		}

		DynamicString &operator=(const DynamicString &other)
		{
			if (this != &other)
				Assign(other.Data(), other.Length());
			return *this;
		}

		DynamicString &operator=(DynamicString &&other) noexcept
		{
			if (this != &other)
			{
				ReleaseHeap();
				AdoptFrom(other);
			}
			return *this;
		}

		DynamicString &operator=(const TChar *str)
		{
			return Assign(str, Traits::Length(str));
		}

		const TChar *CStr() const noexcept
		{
			return _data;
		}

		const TChar *Data() const noexcept
		{
			return _data;
		}

		TChar *Data() noexcept
		{
			return Mutable();
		}

		size_t Capacity() const noexcept
		{
			return _capacity;
		}

		bool IsSmall() const noexcept
		{
			return _data == _buffer;
		}

		using Base::operator[];
		TChar &operator[](size_t index) noexcept
		{
			return Mutable()[index];
		}

		using Base::begin;
		using Base::end;

		TChar *begin() noexcept
		{
			return Mutable();
		}

		TChar *end() noexcept
		{
			return Mutable() + _size;
		}

		void Reserve(size_t capacity)
		{
			if (capacity > _capacity)
				Reallocate(capacity);
		}

		void Clear() noexcept
		{
			_size = 0;
			Mutable()[0] = TChar{};
		}

		void Resize(size_t size, TChar fill = TChar{})
		{
			EnsureCapacity(size);
			for (size_t i = _size; i < size; ++i)
				Mutable()[i] = fill;
			_size = size;
			Mutable()[_size] = TChar{};
		}

		void ShrinkToFit()
		{
			if (IsSmall())
				return;

			if (_size <= SSOCapacity)
			{
				TChar *heap = Mutable();
				Traits::Copy(_buffer, heap, _size);
				_buffer[_size] = TChar{};
				_data = _buffer;
				_capacity = SSOCapacity;
				delete[] heap;
			}
			else if (_size < _capacity)
			{
				Reallocate(_size);
			}
		}

		DynamicString &Assign(const TChar *str, size_t size)
		{
			EnsureCapacity(size);
			Traits::Move(Mutable(), str, size);
			_size = size;
			Mutable()[_size] = TChar{};
			return *this;
		}

		DynamicString &Append(const TChar *str, size_t size)
		{
			if (size == 0)
				return *this;

			const bool aliased = (str >= _data && str < _data + _size);
			const size_t offset = aliased ? static_cast<size_t>(str - _data) : 0;

			EnsureCapacity(_size + size);
			Traits::Copy(Mutable() + _size, aliased ? _data + offset : str, size);

			_size += size;
			Mutable()[_size] = TChar{};
			return *this;
		}

		DynamicString &Append(const Base &view)
		{
			return Append(view.Data(), view.Length());
		}

		DynamicString &Append(TChar value)
		{
			return Append(&value, 1);
		}

		DynamicString &Insert(size_t position, const Base &view)
		{
			if (position > _size)
				position = _size;
			const size_t count = view.Length();
			if (count == 0)
				return *this;

			DynamicString temp(view);
			EnsureCapacity(_size + count);
			Traits::Move(Mutable() + position + count, _data + position, _size - position);
			Traits::Copy(Mutable() + position, temp.Data(), count);
			_size += count;
			Mutable()[_size] = TChar{};
			return *this;
		}

		DynamicString &Remove(size_t position, size_t count = NPos)
		{
			if (position >= _size)
				return *this;
			const size_t removable = _size - position;
			if (count > removable)
				count = removable;

			Traits::Move(Mutable() + position, _data + position + count, _size - position - count);
			_size -= count;
			Mutable()[_size] = TChar{};
			return *this;
		}

		DynamicString &operator+=(const Base &view)
		{
			return Append(view);
		}

		DynamicString &operator+=(const TChar *str)
		{
			return Append(str, Traits::Length(str));
		}

		DynamicString &operator+=(TChar value)
		{
			return Append(value);
		}

	private:
		using Base::_data;
		using Base::_size;

		TChar *Mutable() noexcept
		{
			return const_cast<TChar *>(_data);
		}

		void ResetToSmall() noexcept
		{
			_data = _buffer;
			_size = 0;
			_capacity = SSOCapacity;
			_buffer[0] = TChar{};
		}

		void ReleaseHeap() noexcept
		{
			if (!IsSmall())
				delete[] const_cast<TChar *>(_data);
		}

		void AdoptFrom(DynamicString &other) noexcept
		{
			if (other.IsSmall())
			{
				Traits::Copy(_buffer, other._buffer, other._size + 1);
				_data = _buffer;
				_size = other._size;
				_capacity = SSOCapacity;
			}
			else
			{
				_data = other._data;
				_size = other._size;
				_capacity = other._capacity;
			}
			other.ResetToSmall();
		}

		void EnsureCapacity(size_t required)
		{
			if (required <= _capacity)
				return;

			size_t grown = _capacity + _capacity / 2 + 1;
			if (grown < required)
				grown = required;

			Reallocate(grown);
		}

		void Reallocate(size_t capacity)
		{
			TChar *memory = new TChar[capacity + 1];
			Traits::Copy(memory, _data, _size);
			memory[_size] = TChar{};

			ReleaseHeap();
			_data = memory;
			_capacity = capacity;
		}

		TChar _buffer[SSOBufferCapacity];
		size_t _capacity = SSOCapacity;
	};

	class LETH_CORE_API String : public DynamicString<char, 32>
	{
	public:
		using Base = DynamicString<char, 32>;
		using Base::Base;
		using Base::operator=;

		String() = default;
		String(const String &) = default;
		String(String &&) noexcept = default;
		String &operator=(const String &) = default;
		String &operator=(String &&) noexcept = default;
	};

	inline String operator+(const StringBase<char> &lhs, const StringBase<char> &rhs)
	{
		String result(lhs);
		result.Append(rhs);
		return result;
	}

} // namespace Carc
