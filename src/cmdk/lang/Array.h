#ifndef _LANG_ARRAY_H
#define _LANG_ARRAY_H


#include <vector>
#include <assert.h>
#include <lang/internal/config_inl.h>


namespace lang
{


/** 
 * Simple dynamic array. 
 * @param T Type of array element.
 * @param N Statically allocated buffer size.
 * @author Jani Kajala (jani.kajala@helsinki.fi)
 */
template <class T, int N=1> class Array
{
public:
	/** Creates an empty array. */
	Array() :
		m_data(0), m_cap(0), m_len(0)
	{
	}

	/** Creates an array of n elements. */
	explicit Array( int n ) :
		m_data(0), m_cap(0), m_len(0)
	{
		setSize( n );
	}

	/** Copy by value. */
	Array( const Array<T,N>& other ) :
		m_data(0), m_cap(0), m_len(0)
	{
		*this = other;
	}

	///
	~Array()
	{
		m_dynamicBuffer.clear();
	}

	/** Copy by value. */
	Array& operator=( const Array<T,N>& other )
	{
		setSize( other.m_len );
		for ( int i = 0 ; i < m_len ; ++i )
			m_data[i] = other.m_data[i];
		return *this;
	}

	/** Returns ith element from the array. */
	T& operator[]( int index )
	{
		assert( index >= 0 && index < m_len );
		return m_data[index];
	}

	/** Adds an element to the end of the array. */
	void add( const T& item )
	{
		T itemCopy( item );
		if ( m_len == m_cap )
			realloc( m_len+1 );
		m_data[m_len++] = itemCopy;
	}

	/** Adds an element before specified index. */
	void add( int index, const T& item )
	{
		assert( index >= 0 && index <= size() );

		T itemCopy( item );
		setSize( m_len + 1 );
		rcopy( m_data+(index+1), m_data+index, m_len-(index+1) );
		m_data[index] = itemCopy;
	}

	/** Sets number of elements in the array. */
	void setSize( int size )
	{
		for ( int i = size ; i < m_len ; ++i )
			m_data[i] = T();

		if ( size > m_cap )
			realloc( size );
		else if (m_len > N) m_dynamicBuffer.resize(size);

		m_len = size;
		assert(m_len <= N || (m_dynamicBuffer.size() == m_len && m_dynamicBuffer.capacity() == m_cap));
	}

	/** Sets number of elements in the array to 0. */
	void clear()
	{
		setSize( 0 );
	}

	/** Returns pointer to the beginning of the array (inclusive). */
	T* begin()
	{
		return m_data;
	}

	/** Returns pointer to the end of the array (exclusive). */
	T* end()
	{
		return m_data+m_len;
	}

	/** Returns ith element from the array. */
	const T& operator[]( int index ) const
	{
		assert( index >= 0 && index < m_len );
		return m_data[index];
	}

	/** Returns number of elements in the array. */
	int size() const
	{
		return m_len;
	}

	/** Returns pointer to the beginning of the array (inclusive). */
	const T* begin() const
	{
		return m_data;
	}

	/** Returns pointer to the end of the array (exclusive). */
	const T* end() const
	{
		return m_data+m_len;
	}

private:
	typedef std::vector<T> Vec;
	T*		m_data;
	int		m_cap;
	int		m_len;
	Vec		m_dynamicBuffer;
	T		m_staticBuffer[N];

	void realloc( int size )
	{
		if ( size > N ) // требуемый размер не может быть умещен в статическом массиве
		{
			if (m_len <= N) // если текущие данные лежат в статическом буфере, перегоняем их в динамический
			{
				for ( int i = 0 ; i < m_len ; ++i ) 
				{
					m_dynamicBuffer.push_back(m_staticBuffer[i]);
					m_staticBuffer[i] = T();				
				}
			}
			m_dynamicBuffer.resize(size);

			m_data = &m_dynamicBuffer[0];
			m_cap = m_dynamicBuffer.capacity();
		}
		else // данные нового размера умещаются в статическом буфере
		{	
			if ( m_len > N ) // если текущие данные лежат в динамическом буфере, перегоняем их в статический
			{
				assert( size < m_len );
				for ( int i = 0 ; i < size ; ++i )
				{
					m_staticBuffer[i] = m_dynamicBuffer[i];
				}
				m_dynamicBuffer.clear();
			}

			m_data = m_staticBuffer;
			m_cap = N;
		}
	}

	/** Copy in reverse order. */
	void rcopy( T* dst, const T* src, int count )
	{
		for ( int i = count-1 ; i >= 0 ; --i )
			dst[i] = src[i];
	}
};


} // lang


#endif // _LANG_ARRAY_H
