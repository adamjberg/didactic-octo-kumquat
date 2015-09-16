#include "tweens/Tween.h"

Tween::Tween( float &value, float from, float to, int duration, easing_function easing, callback_function onCompleteFunction, callback_function onUpdateFunction ) : value( value ), from( from ), to( to ), duration( duration ), position( 0 ), easing( easing )
{
	value = from;
	if( onCompleteFunction )
	{
		onComplete.add( onCompleteFunction );
	}
	if( onUpdateFunction )
	{
		onUpdate.add( onUpdateFunction );
	}
}

float Tween::update( int dt )
{
	const int t( std::min( duration - position, dt ) );
	position += t;
	const float coeff = easing( static_cast< float >( position ) / duration );
	value = from + coeff * ( to - from );

	onUpdate.dispatch( value );

	if( position == duration )
	{
		onComplete.dispatch( value );
	}

	return value;
}
