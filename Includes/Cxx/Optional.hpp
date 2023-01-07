#ifndef BEAE9345_441A_49A7_AB8A_28C3C1F463AD
#define BEAE9345_441A_49A7_AB8A_28C3C1F463AD

#include <optional>
#include <concepts>

namespace Cxx
{
  template <typename Type>
  struct Optional : public std::optional<Type>
  {
      using BaseType = std::optional<Type>;

      using BaseType::optional;
      using BaseType::operator=;

      template <typename Self, std::integral... Indexes>
      constexpr auto&& operator[](this Self&& This, const Indexes... Index)
      {
        return This.operator[](Index...);
      }

      template <typename Self>
      constexpr auto&& operator*(this Self&& This)
      {
        if constexpr ( requires { *This.value(); } )
        {
          return *This.value();
        }
        else if constexpr ( requires { *This.value().get(); } )
        {
          return *This.value().get();
        }
        else if constexpr ( requires { This.value().get(); } )
        {
          return This.value().get();
        }
        else
        {
          return This.value();
        }
      }

      template <typename Self>
      constexpr auto&& operator->(this Self&& This)
      {
        if constexpr ( requires { This.value().operator->(); } )
        {
          return This.value();
        }
        else
        {
          return This.BaseType::operator->();
        }
      }
  };
} // namespace Cxx

#endif /* BEAE9345_441A_49A7_AB8A_28C3C1F463AD */
