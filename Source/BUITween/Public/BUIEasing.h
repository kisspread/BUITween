#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EBUIEasingType : uint8
{
	Linear,
	Smoothstep,
	InSine,
	OutSine,
	InOutSine,
	InQuad,
	OutQuad,
	InOutQuad,
	InCubic,
	OutCubic,
	InOutCubic,
	InQuart,
	OutQuart,
	InOutQuart,
	InQuint,
	OutQuint,
	InOutQuint,
	InExpo,
	OutExpo,
	InOutExpo,
	InCirc,
	OutCirc,
	InOutCirc,
	InElastic,
	OutElastic,
	InOutElastic,
	InBack,
	OutBack,
	InOutBack,
};

struct FBUIEasing
{
public:
	
	static float Ease( EBUIEasingType Type, float time, float duration = 1.0f, float overshootOrAmplitude = 0.1f, float period = 1.0f )
	{
		switch ( Type )
		{
			case EBUIEasingType::Linear: return Linear( time, duration ); 
			case EBUIEasingType::Smoothstep: return Smoothstep( time, 0, duration); 
			case EBUIEasingType::InSine: return InSine( time, duration ); 
			case EBUIEasingType::OutSine: return OutSine( time, duration ); 
			case EBUIEasingType::InOutSine: return InOutSine( time, duration ); 
			case EBUIEasingType::InQuad: return InQuad( time, duration ); 
			case EBUIEasingType::OutQuad: return OutQuad( time, duration ); 
			case EBUIEasingType::InOutQuad: return InOutQuad( time, duration ); 
			case EBUIEasingType::InCubic: return InCubic( time, duration ); 
			case EBUIEasingType::OutCubic: return OutCubic( time, duration ); 
			case EBUIEasingType::InOutCubic: return InOutCubic( time, duration ); 
			case EBUIEasingType::InQuart: return InQuart( time, duration ); 
			case EBUIEasingType::OutQuart: return OutQuart( time, duration ); 
			case EBUIEasingType::InOutQuart: return InOutQuart( time, duration ); 
			case EBUIEasingType::InQuint: return InQuint( time, duration ); 
			case EBUIEasingType::OutQuint: return OutQuint( time, duration ); 
			case EBUIEasingType::InOutQuint: return InOutQuint( time, duration ); 
			case EBUIEasingType::InExpo: return InExpo( time, duration ); 
			case EBUIEasingType::OutExpo: return OutExpo( time, duration ); 
			case EBUIEasingType::InOutExpo: return InOutExpo( time, duration ); 
			case EBUIEasingType::InCirc: return InCirc( time, duration ); 
			case EBUIEasingType::OutCirc: return OutCirc( time, duration ); 
			case EBUIEasingType::InOutCirc: return InOutCirc( time, duration ); 
			case EBUIEasingType::InElastic: return InElastic( time, duration, overshootOrAmplitude, period ); 
			case EBUIEasingType::OutElastic: return OutElastic( time, duration, overshootOrAmplitude, period ); 
			case EBUIEasingType::InOutElastic: return InOutElastic( time, duration, overshootOrAmplitude, period ); 
			case EBUIEasingType::InBack: return InBack( time, duration, overshootOrAmplitude, period ); 
			case EBUIEasingType::OutBack: return OutBack( time, duration, overshootOrAmplitude, period ); 
			case EBUIEasingType::InOutBack: return InOutBack( time, duration, overshootOrAmplitude, period ); 
		}
		return 0;
	}

	static float Linear( float time, float duration = 1.0f )
	{
		return time / duration;
	}

	static float Smoothstep( float x, float edge0 = 0.0f, float edge1 = 1.0f )
	{
		x = FMath::Clamp<float>( ( x - edge0 ) / ( edge1 - edge0 ), 0.0, 1.0 );
		return x*x*( 3 - 2 * x );
	}

	static float InSine( float time, float duration = 1.0f )
	{
		return -( float ) FMath::Cos( time / duration * HALF_PI ) + 1;
	}

	static float OutSine( float time, float duration = 1.0f )
	{
		return ( float ) FMath::Sin( time / duration * HALF_PI );
	}

	static float InOutSine( float time, float duration = 1.0f )
	{
		return -0.5f * ( ( float ) FMath::Cos( PI * time / duration ) - 1 );
	}

	static float InQuad( float time, float duration = 1.0 )
	{
		time /= duration;
		return time * time;
	}

	static float OutQuad( float time, float duration = 1.0f )
	{
		time /= duration;
		return -time * ( time - 2 );
	}

	static float InOutQuad( float time, float duration = 1.0f )
	{
		time /= duration * 0.5f;
		if ( time < 1 )
			return 0.5f * time * time;
		--time;
		return -0.5f * ( time * ( time - 2 ) - 1 );
	}

		static float InCubic( float time, float duration = 1.0f )
		{
			time /= duration;
			return time * time * time;
		}

		static float OutCubic( float time, float duration = 1.0f )
		{
			time = time / duration - 1;
			return ( time * time * time + 1 );
		}

	static float InOutCubic( float time, float duration = 1.0f )
	{
		time /= duration * 0.5f;
		if ( time < 1 )
			return 0.5f * time * time * time;
		time -= 2;
		return 0.5f * ( time * time * time + 2 );
	}

	static float InQuart( float time, float duration = 1.0f )
	{
		time /= duration;
		return time * time * time * time;
	}

	static float OutQuart( float time, float duration = 1.0f )
	{
		time = time / duration - 1;
		return -( time * time * time * time - 1 );
	}

	static float InOutQuart( float time, float duration = 1.0f )
	{
		time /= duration * 0.5f;
		if ( time < 1 )
			return 0.5f * time * time * time * time;
		time -= 2;
		return -0.5f * ( time * time * time * time - 2 );
	}

	static float InQuint( float time, float duration = 1.0f )
	{
		time /= duration;
		return time * time * time * time * time;
	}

	static float OutQuint( float time, float duration = 1.0f )
	{
		time = time / duration - 1;
		return ( time * time * time * time * time + 1 );
	}

	static float InOutQuint( float time, float duration = 1.0f )
	{
		time /= duration * 0.5f;
		if ( time < 1 )
			return 0.5f * time * time * time * time * time;
		time -= 2;
		return 0.5f * ( time * time * time * time * time + 2 );
	}

	static float InExpo( float time, float duration = 1.0f )
	{
		return ( time == 0 ) ? 0 : ( float )FMath::Pow( 2, 10 * ( time / duration - 1 ) );
	}

	static float OutExpo( float time, float duration = 1.0f )
	{
		if ( time == duration )
			return 1;
		return ( -( float ) FMath::Pow( 2, -10 * time / duration ) + 1 );
	}

	static float InOutExpo( float time, float duration = 1.0f )
	{
		if ( time == 0 )
			return 0;
		if ( time == duration )
			return 1;
		time /= duration;
		if ( ( time * 0.5f ) < 1 )
			return 0.5f * ( float )FMath::Pow( 2, 10 * ( time - 1 ) );
		--time;
		return 0.5f * ( -( float ) FMath::Pow( 2, -10 * time ) + 2 );
	}

	static float InCirc( float time, float duration = 1.0f )
	{
		time /= duration;
		return -( ( float ) FMath::Sqrt( 1 - time * time ) - 1 );
	}

	static float OutCirc( float time, float duration = 1.0f )
	{
		time = time / duration - 1;
		return ( float ) FMath::Sqrt( 1 - time * time );
	}

	static float InOutCirc( float time, float duration = 1.0f )
	{
		time /= duration * 0.5f;
		if ( time < 1 )
			return -0.5f * ( ( float ) FMath::Sqrt( 1 - time * time ) - 1 );
		time -= 2;
		return 0.5f * ( ( float ) FMath::Sqrt( 1 - time * time ) + 1 );
	}

	static float InElastic( float time, float duration = 1.0f, float overshootOrAmplitude = 0.1f, float period = 1.0f )
	{
		float s0;
		if ( time == 0 ) return 0;
		if ( ( time /= duration ) == 1 ) return 1;
		if ( period == 0 ) period = duration * 0.3f;
		if ( overshootOrAmplitude < 1 ) {
			overshootOrAmplitude = 1;
			s0 = period / 4;
		}
		else s0 = period / TWO_PI * ( float ) FMath::Asin( 1 / overshootOrAmplitude );
		time -= 1;
		return -( overshootOrAmplitude * ( float ) FMath::Pow( 2, 10 * time ) * ( float ) FMath::Sin( ( time * duration - s0 ) * TWO_PI / period ) );
	}

	static float OutElastic( float time, float duration = 1.0f, float overshootOrAmplitude = 0.1f, float period = 1.0f )
	{
		float s1;
		if ( time == 0 ) return 0;
		time /= duration;
		if ( time == 1 ) return 1;
		if ( period == 0 ) period = duration * 0.3f;
		if ( overshootOrAmplitude < 1 ) {
			overshootOrAmplitude = 1;
			s1 = period / 4;
		}
		else s1 = period / TWO_PI * ( float ) FMath::Asin( 1 / overshootOrAmplitude );
		return ( overshootOrAmplitude * ( float ) FMath::Pow( 2, -10 * time ) * ( float ) FMath::Sin( ( time * duration - s1 ) * TWO_PI / period ) + 1 );
	}

	static float InOutElastic( float time, float duration = 1.0f, float overshootOrAmplitude = 0.1f, float period = 1.0f )
	{
		float s;
		if ( time == 0 ) return 0;
		time /= duration;
		if ( time == 1 ) return 1;
		if ( period == 0 ) period = duration * ( 0.3f * 1.5f );
		if ( overshootOrAmplitude < 1 ) {
			overshootOrAmplitude = 1;
			s = period / 4;
		}
		else s = period / TWO_PI * ( float ) FMath::Asin( 1 / overshootOrAmplitude );

		time *= 2; // Scale time to 0-2

		if ( time < 1 )
		{
			time -= 1;
			return -0.5f * ( overshootOrAmplitude * ( float ) FMath::Pow( 2, 10 * time ) * ( float ) FMath::Sin( ( time * duration - s ) * TWO_PI / period ) );
		}
		else
		{
			time -= 1; // Adjust for the second half
			return overshootOrAmplitude * ( float ) FMath::Pow( 2, -10 * time ) * ( float ) FMath::Sin( ( time * duration - s ) * TWO_PI / period ) * 0.5f + 1;
		}
	}

	static float InBack( float time, float duration = 1.0f, float overshootOrAmplitude = 0.1f, float period = 1.0f )
	{
		time /= duration;
		return time * time * ( ( overshootOrAmplitude + 1 ) * time - overshootOrAmplitude );
	}

	static float OutBack( float time, float duration = 1.0f, float overshootOrAmplitude = 0.1f, float period = 1.0f )
	{
		time = time / duration - 1;
		return ( time * time * ( ( overshootOrAmplitude + 1 ) * time + overshootOrAmplitude ) + 1 );
	}

	static float InOutBack( float time, float duration = 1.0f, float overshootOrAmplitude = 0.1f, float period = 1.0f )
	{
		time /= duration * 0.5f;
		overshootOrAmplitude *= 1.525f;
		if ( time < 1 )
			return 0.5f * ( time * time * ( ( overshootOrAmplitude + 1 ) * time - overshootOrAmplitude ) );
		time -= 2;
		return 0.5f * ( time * time * ( ( overshootOrAmplitude + 1 ) * time + overshootOrAmplitude ) + 2 );
	}

};


