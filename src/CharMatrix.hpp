
// PeykNowruzi - Basic ASCII-Art Generator
// Copyright (C) 2021-2022 Kasra Hashemi

/*

 This file is part of PeykNowruzi.

 PeykNowruzi is free software: you can redistribute it and/or modify it
 under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License,
 or (at your option) any later version.

 PeykNowruzi is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty
 of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along
 with PeykNowruzi. If not, see <https://www.gnu.org/licenses/>.

*/


#pragma once

#include "pch.hpp"


namespace peyknowruzi
{

inline constexpr std::streamsize default_buffer_size { 169 };

template < class Allocator = std::allocator<char> >
class CharMatrix
{
public:
	static constexpr std::uint32_t default_y_axis_len { 20 };
	static constexpr std::uint32_t default_x_axis_len { 20 };
	static constexpr char default_fill_character { ' ' };
	static constexpr std::size_t cartesian_components_count { 4 };
	static constexpr std::size_t matrix_attributes_count { 3 };

private:
	enum AllowedChars : char
	{
		Dash		  = '-' ,
		BackSlash	  = '\\',
		ForwardSlash  = '/' ,
		VerticalSlash = '|' ,
	};

	inline static const std::unordered_set< AllowedChars > chars_for_drawing { Dash,
																			   BackSlash,
																			   ForwardSlash,
																			   VerticalSlash };

public:
	explicit CharMatrix( const std::uint32_t Y_AxisLen = default_y_axis_len,
						 const std::uint32_t X_AxisLen = default_x_axis_len,
						 const char fillCharacter = default_fill_character,
						 const Allocator& alloc = Allocator { } );
	CharMatrix( CharMatrix&& rhs ) noexcept;
	CharMatrix& operator=( CharMatrix&& rhs ) noexcept;

	explicit operator bool( ) const noexcept;
	bool operator==( const CharMatrix& rhs ) const noexcept;
	std::partial_ordering operator<=>( const CharMatrix& rhs ) const noexcept;
	char& operator[ ]( const std::size_t X_Axis, const std::size_t Y_Axis ) noexcept;
	const char& operator[ ]( const std::size_t X_Axis, const std::size_t Y_Axis ) const noexcept;

	[[ nodiscard ]] const std::uint32_t& getY_AxisLen( ) const noexcept;
	[[ nodiscard ]] const std::uint32_t& getX_AxisLen( ) const noexcept;
	[[ nodiscard ]] const char& getFillCharacter( ) const noexcept;
	[[ nodiscard ]] const std::vector<char, Allocator>& getCharacterMatrix( ) const noexcept;

	void setY_AxisLen( const std::uint32_t Y_AxisLen );
	void setX_AxisLen( const std::uint32_t X_AxisLen );
	void setFillCharacter( const char fillCharacter );
	void setCharacterMatrix( const std::array<std::uint32_t, cartesian_components_count>&
							 coordsOfChar ) noexcept;

	[[ nodiscard ]] bool
	validateEnteredCoords( const std::string_view str_enteredCoords,
						   std::array<std::uint32_t, cartesian_components_count>&
						   int_enteredCoords_OUT ) const noexcept;

	[[ nodiscard ]] static bool
	validateEnteredMatrixAttributes( const std::string_view str_enteredMatrixAttributes,
									 std::tuple<std::uint32_t, std::uint32_t, char>&
									 tuple_enteredMatrixAttributes_OUT ) noexcept;

	[[ nodiscard ]] static std::optional<AllowedChars>
	processCoordsToObtainCharType( const std::array<std::uint32_t, cartesian_components_count>&
								   coordsOfChar ) noexcept;

	[[ nodiscard ]] std::size_t getNumOfInputLines( ) const;
	[[ nodiscard ]] static auto getMatrixAttributes( );
	void getCoords( );
	void draw( std::ostream& output_stream ) const;

	template <class Alloc>
	friend std::ofstream& operator<<( std::ofstream& ofs, const CharMatrix<Alloc>& char_matrix );
	template <class Alloc>
	friend std::ifstream& operator>>( std::ifstream& ifs, CharMatrix<Alloc>& char_matrix );

private:
	std::uint32_t m_Y_AxisLen;
	std::uint32_t m_X_AxisLen;
	char m_fillCharacter;
	std::vector<char, Allocator> m_characterMatrix;
};

namespace pmr
{
	using CharMatrix = peyknowruzi::CharMatrix< std::pmr::polymorphic_allocator<char> >;
}


void initialize( );
void runScript( );

}

namespace std
{

template <class Allocator>
struct hash< peyknowruzi::CharMatrix<Allocator> >
{
	using argument_type = peyknowruzi::CharMatrix<Allocator>;
	using result_type = std::size_t;

	result_type operator( )( const argument_type& char_matrix ) const;
};

}
