from setuptools import setup, Extension
from Cython.Build import cythonize

# Explicitly set the module name as 'matrix'
extensions = [
    Extension(
        name="matrix",  # Desired module name
        sources=["multiply.pyx"],  # Cython source file
    )
]

setup(
    name="matrix",
    ext_modules=cythonize(extensions, compiler_directives={"language_level": "3"}),
    zip_safe=False,
)