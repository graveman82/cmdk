#ifndef _LANG_NUMBERREADER_H
#define _LANG_NUMBERREADER_H


namespace lang
{


/**
 * Finite automaton for extracting numeric value from character sequence
 * one character at a time. 
 *
 * Only English/US locale is supported. This class 
 * is not really suitable for reading user input but
 * for example parsing text data.
 *
 * Usage example:
   <pre>
	NumberReader(float) floatReader;

	const char* str = "123.123";
	for ( ; floatReader.put(*str) ; ++str );
	float value = floatReader.value();
	
	assert( value == 123.123f );
	</pre>
 *
 * @author Jani Kajala (jani.kajala@helsinki.fi)
 */
template <class T> class NumberReader
{
public:
	///
	NumberReader();

	/** 
	 * Appends a character to string representation to be converted to numeric value.
	 * If character is not accepted then the reader is reset to initial state.
	 *
	 * @return Number of characters accepted (either 0 or 1).
	 */
	int			put( char ch );

	/// Returns current input converted to numeric value.
	const T&	value() const;

	/// Returns true if the input describes valid numeric value.
	bool		valid() const;
};


// NumberReader specialization for double.
template <> class NumberReader<double>
{
public:
	NumberReader()																	{m_state=STATE_INIT; m_valid=false;}

	int			put( char ch );
/* M.Sungatullin [26.11.2016]:
 Explicit specializations no longer find template parameters from primary template in MSVC 2008.
 The use of T from the primary template is not allowed in the explicit specialization. For code
 to be valued in MSVC 2008 all instances of the template parameter replaced in the specialization 
 with the explicitly specialized type.
*/
#ifdef _MSC_VER
	#if _MSC_VER >= 1500 // MSVC 2008
	double		value() const;
	#else
	T			value() const;
	#endif
#endif
	bool		valid() const														{return m_valid;}

private:
	enum State
	{
		// initial state
		STATE_INIT,
		// [\+|\-]_STATE_BODY
		STATE_SIGN,
		// {._STATE_FRACTION|<d>+[._STATE_FRACTION]}[e_STATE_EXP|E_STATE_EXP]
		STATE_BODY,
		// {<d>*}[e_STATE_EXP|E_STATE_EXP]
		STATE_FRACTION,
		// [\+|\-]_STATE_EXP_BODY
		STATE_EXP,
		// {.STATE_EXP_FRACTION|<d>+[.STATE_EXP_FRACTION]}
		STATE_EXP_BODY,
		// <d>*
		STATE_EXP_FRACTION,
	};

	bool		m_valid;
	State		m_state;
#ifdef _MSC_VER
	#if _MSC_VER >= 1500 // MSVC 2008
	double		m_sign;
	double		m_value;
	double		m_fractionScale;
	double		m_expSign;
	double		m_expValue;
	#else
	T			m_sign;
	T			m_value;
	T			m_fractionScale;
	T			m_expSign;
	T			m_expValue;
	#endif
#endif
};

// NumberReader specialization for float.
template <> class NumberReader<float>
{
public:
	NumberReader()																	{}

	int			put( char ch )														{return m_impl.put(ch);}
// M.Sungatullin [26.11.2016]: to meet explicit specialization rules in the MSVC 2008.
#ifdef _MSC_VER
	#if _MSC_VER >= 1500 // MSVC 2008
	float		value() const														{return (float)m_impl.value();}
	#else
	T			value() const														{return (T)m_impl.value();}
	#endif
#endif
	bool		valid() const														{return m_impl.valid();}

private:
	NumberReader<double>	m_impl;
};

// NumberReader specialization for long.
template <> class NumberReader<long>
{
public:
	NumberReader()																	{m_state=STATE_INIT; m_valid=false;}

	int			put( char ch );
// M.Sungatullin [26.11.2016]: to meet explicit specialization rules in the MSVC 2008.
#ifdef _MSC_VER
	#if _MSC_VER >= 1500 // MSVC 2008
	long		value() const;
	#else
	T			value() const;
	#endif
#endif
	bool		valid() const														{return m_valid;}

private:
	enum State
	{
		// initial state
		STATE_INIT,
		// [\+|\-]_STATE_BODY
		STATE_SIGN,
		// <d>+
		STATE_BODY,
	};

	bool		m_valid;
	State		m_state;
// M.Sungatullin [26.11.2016]: to meet explicit specialization rules in the MSVC 2008.
#ifdef _MSC_VER
	#if _MSC_VER >= 1500 // MSVC 2008
	long		m_sign;
	long		m_value;
	#else
	T			m_sign;
	T			m_value;
	#endif
#endif
};

// NumberReader specialization for int.
template <> class NumberReader<int>
{
public:
	NumberReader()																	{}

	int			put( char ch )														{return m_impl.put(ch);}
// M.Sungatullin [26.11.2016]: to meet explicit specialization rules in the MSVC 2008.
#ifdef _MSC_VER
	#if _MSC_VER >= 1500 // MSVC 2008
	int			value() const														{return (int)m_impl.value();}
	#else
	T			value() const														{return (T)m_impl.value();}
	#endif
#endif
	bool		valid() const														{return m_impl.valid();}

private:
	NumberReader<long>	m_impl;
};

// NumberReader specialization for short.
template <> class NumberReader<short>
{
public:
	NumberReader()																	{}

	int			put( char ch )														{return m_impl.put(ch);}
// M.Sungatullin [26.11.2016]: to meet explicit specialization rules in the MSVC 2008.
#ifdef _MSC_VER
	#if _MSC_VER >= 1500 // MSVC 2008
	short		value() const														{return (short)m_impl.value();}
	#else
	T			value() const														{return (T)m_impl.value();}
	#endif
#endif
	bool		valid() const														{return m_impl.valid();}

private:
	NumberReader<long>	m_impl;
};

// NumberReader specialization for unsigned long.
template <> class NumberReader<unsigned long>
{
public:
	NumberReader()																	{m_state=STATE_INIT; m_valid=false;}

	int			put( char ch );
// M.Sungatullin [26.11.2016]: to meet explicit specialization rules in the MSVC 2008.
#ifdef _MSC_VER
	#if _MSC_VER >= 1500 // MSVC 2008
	unsigned long	value() const;
	#else
	T			value() const;
	#endif
#endif
	bool		valid() const														{return m_valid;}

private:
	enum State
	{
		// initial state
		STATE_INIT,
		// <d>+
		STATE_BODY,
	};

	bool		m_valid;
	State		m_state;
// M.Sungatullin [26.11.2016]: to meet explicit specialization rules in the MSVC 2008.
#ifdef _MSC_VER
	#if _MSC_VER >= 1500 // MSVC 2008
	unsigned long	m_value;
	#else
	T			m_value;
	#endif
#endif
};

// NumberReader specialization for unsigned int.
template <> class NumberReader<unsigned>
{
public:
	NumberReader()																	{}

	int			put( char ch )														{return m_impl.put(ch);}
// M.Sungatullin [26.11.2016]: to meet explicit specialization rules in the MSVC 2008.
#ifdef _MSC_VER
	#if _MSC_VER >= 1500 // MSVC 2008
	unsigned	value() const														{return (unsigned)m_impl.value();}
	#else
	T			value() const														{return (T)m_impl.value();}
	#endif
#endif
	bool		valid() const														{return m_impl.valid();}

private:
	NumberReader<unsigned long>	m_impl;
};

// NumberReader specialization for unsigned short.
template <> class NumberReader<unsigned short>
{
public:
	NumberReader()																	{}

	int			put( char ch )														{return m_impl.put(ch);}
// M.Sungatullin [26.11.2016]: to meet explicit specialization rules in the MSVC 2008.
#ifdef _MSC_VER
	#if _MSC_VER >= 1500 // MSVC 2008
	unsigned short	value() const														{return (unsigned short)m_impl.value();}
	#else
	T			value() const														{return (T)m_impl.value();}
	#endif
#endif
	bool		valid() const														{return m_impl.valid();}

private:
	NumberReader<unsigned long>	m_impl;
};


} // lang


#endif // _LANG_NUMBERREADER_H
