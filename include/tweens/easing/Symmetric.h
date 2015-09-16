#pragma once

namespace easing
{
	template<float( *Function )( float )>
	class Symmetric
	{
	public:
		static float ease_in( float t );
		static float ease_out( float t );
		static float ease_in_out( float t );
	};
}

template<float( *Function )( float )>
float easing::Symmetric<Function>::ease_in( float t )
{
	return Function( t );
}

template<float( *Function )( float )>
float easing::Symmetric<Function>::ease_out( float t )
{
	return 1 - ease_in( 1 - t );
}

template<float( *Function )( float )>
float easing::Symmetric<Function>::ease_in_out( float t )
{
	if( t < 0.5 )
	{
		return ease_in( 2 * t ) / 2;
	}
	else
	{
		return ease_out( 2 * t - 1 ) / 2
	}
}