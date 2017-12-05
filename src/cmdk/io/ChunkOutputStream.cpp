#include "ChunkOutputStream.h"
#include <io/DataOutputStream.h>
#include <io/ByteArrayOutputStream.h>
#include <io/IOException.h>
#include <vector>
#include <stdint.h>
#include "config.h"

//-----------------------------------------------------------------------------

using namespace lang;

//-----------------------------------------------------------------------------

namespace io
{


static void writeVarInt( DataOutputStream* out, int value )
{
	int		uns		= value;
	int		bits	= 0;

	if ( uns < 0 )
	{
		uns = -uns;
		bits += 2;
	}

	bits = 0xFF & (uns << 2);
	uns >>= 6;
	if ( 0 != uns )
		bits += 1;
	out->writeByte( bits );

	while ( 0 != (1&bits) )
	{
		bits = 0xFF & (uns << 1);
		uns >>= 7;
		if ( 0 != uns )
			bits += 1;
		out->writeByte( bits );
	}
}

//-----------------------------------------------------------------------------

class ChunkOutputStream::ChunkOutputStreamImpl :
	public Object
{
public:
	OutputStream*				fileout;
	ByteArrayOutputStream		bytebuf;
	DataOutputStream			byteout;
	std::vector<uint8_t>		data;
	std::vector<int>			chunkBegins;
	std::vector<String>			chunkNames;

	ChunkOutputStreamImpl( OutputStream* out ) :
		fileout(out), 
		byteout( &bytebuf )
	{
	}

	void beginChunk( const String& name )
	{
		bytebuf.reset();
		byteout.writeUTF( name );
		byteout.writeInt( 0 );
		appendBytes();

		chunkBegins.push_back( data.size() );
		chunkNames.push_back( name );
	}

	void endChunk()
	{
		if ( chunkBegins.size() < 1 )
			throw IOException( Format("Unpaired end chunk when writing {0}", fileout->toString()) );

		String name = chunkNames.back();
		chunkNames.pop_back();

		int chunkBegin = chunkBegins.back();
		chunkBegins.pop_back();
		int chunkSize = data.size() - chunkBegin;
		if ( chunkSize < 0 || chunkBegin < 4 || chunkBegin > (int)data.size() )
			throw IOException( Format("Invalid chunk {0} size when writing {1}", name, fileout->toString()) );

		bytebuf.reset();
		byteout.writeInt( chunkSize );
		bytebuf.toByteArray( &data[0]+chunkBegin-4, 4 );

		// end of top-level chunk?
		if ( 0 == chunkBegins.size() )
			close();
	}

	void writeByte( int v )
	{
		bytebuf.reset();
		byteout.writeByte( v );
		appendBytes();
	}

	void writeInt( int v )
	{
		bytebuf.reset();
		writeVarInt( &byteout, v );
		appendBytes();
	}

	void writeFloat( float v )
	{
		bytebuf.reset();
		byteout.writeFloat( v );
		appendBytes();
	}

	void writeString( const String& v )
	{
		bytebuf.reset();
		byteout.writeUTF( v );
		appendBytes();
	}

	void appendBytes()
	{
		int oldsize = data.size();
		int bytes = bytebuf.size();
		data.resize( oldsize + bytes );
		bytebuf.toByteArray( &data[0] + oldsize, bytes );
	}

	void close()
	{
		fileout->write( &data[0], data.size() );
		data.clear();
	}

private:
	ChunkOutputStreamImpl( const ChunkOutputStreamImpl& );
	ChunkOutputStreamImpl& operator=( const ChunkOutputStreamImpl& );
};

//-----------------------------------------------------------------------------

ChunkOutputStream::ChunkOutputStream( OutputStream* out ) :
	FilterOutputStream( out )
{
	m_this = new ChunkOutputStreamImpl( out );
}

ChunkOutputStream::~ChunkOutputStream()
{
}

void ChunkOutputStream::beginChunk( const String& name )
{
	m_this->beginChunk( name );
}

void ChunkOutputStream::endChunk()
{
	m_this->endChunk();
}

void ChunkOutputStream::writeInt( int v )
{
	m_this->writeInt( v );
}

void ChunkOutputStream::writeFloat( float v )
{
	m_this->writeFloat( v );
}

void ChunkOutputStream::writeString( const String& v )
{
	m_this->writeString( v );
}

void ChunkOutputStream::close()
{
	m_this->close();
}

long ChunkOutputStream::size() const
{
	return m_this->data.size();
}

void ChunkOutputStream::writeByte( int v )
{
	m_this->writeByte( v );
}


} // io
