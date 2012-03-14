/** \file mat.h 
 * \brief Contains class declaration for pcl2::Mat
 */

#ifndef PCL2_MATRIX_H
#define PCL2_MATRIX_H

#include <boost/shared_ptr.hpp>

namespace pcl2
{

// Forward declarations
namespace core
{
class MatImpl;
}

template <typename T> class TypedMat;

/** \brief This class defines a shared 2D matrix object and serves as the core 
 * matrix data structure in PCL
 *
 * This is the data structure in which all point data is stored (e.g., a point's
 * x,y,z-position, color, 3D surface normal, feature descritor, etc.).  When
 * representing point data, each row of the matrix will represent a single 
 * point, and each column will represent a dimension.  For example, a cloud of N
 * 3-dimensional points, will be stored as an N by 3 Mat.  Such Mats of
 * point data are often labeled with a channel name (e.g., "xyz") and stored in 
 * a Cloud object so that multiple channels of data can be associated together.
 *
 * \note This class serves as a pointer to the actual data, so copying this 
 * object does not create a unique copy of its data.  The actual implementation
 * (i.e., the data and methods for operating on it) is contained in an internal
 * MatImpl object.  These MatImpl classes should never be used directly.
 *
 * \see TypedMat
 * \see EigenMat
 */
class Mat
{
private:
  Mat ();

protected:
  /** \brief A shared pointer to the implementation */
  typedef boost::shared_ptr<core::MatImpl> MatImplPtr;

  /** \brief Construct a Mat around the provided MatImpl */
  Mat (const MatImplPtr matrix_ptr);

  /** \brief Get the shared pointer to the underlying MatImpl
   *
   * \return A shared pointer to the underlying MatImpl
   */
  virtual MatImplPtr getPtr ();

  /** \brief Get a const shared pointer to the underlying Mat
   *
   * \return A shared pointer to the underlying Mat
   */
  virtual const MatImplPtr getPtr () const;

public:
  /** \brief Create a new copy of this matrix and its data
   *
   * \return A shared matrix with a new copy of the underlying data
   */
  virtual Mat copy () const;

  /** \brief Get the number of rows in the matrix
   *
   * \return The number of rows in the matrix
   */
  virtual size_t rows () const;

  /** \brief Get the number of columns in the matrix
   *
   * \return The number of columns in the matrix
   */
  virtual size_t cols () const;

  /** \brief  Create a view of a subset of rows in this matrix 
   *
   * This operator creates a view of the matrix based on a matrix of indices.  
   * The resulting view will contain a row for each row index defined in 
   * \a indices.  The elements in each row of the view will be references to the
   * corresponding elements in the original matrix.
   * 
   * Note that the matrix data is not copied; any changes made to the view's data
   * will also affect the corresponding values in the original matrix and vice 
   * versa.
   *
   * \param indices An N by 1 matrix of integer indices in the matrix.  Each 
   * element in must be a valid row index in the matrix.
   * \return An NxM matrix referencing the rows indexed by \a indices, where N is
   * the number of rows in \a indices and M is the number of columns in the
   * original matrix.
   */
  Mat operator () (const TypedMat<int> & indices);

protected:
  /** A pointer to the underlying MatImpl containing the actual data */
  boost::shared_ptr<core::MatImpl> matrix_ptr_;

  template <typename T> friend class TypedMat;

};

}

#endif
