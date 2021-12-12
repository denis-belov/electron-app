import './index.scss';
import '@babel/polyfill';



const WINDOW_WIDTH = 800;
const WINDOW_HEIGHT = 600;



const
	{
		testRenderingThread,
		runRenderingThread,
		getPixelDataStorageIsAllocated,
		getPixelDataStorage,
		// rotateOrbitJs,
	}	= window.__CPP_MODULE__;



// LOG(__CPP_MODULE__)



const [ canvas ] = document.getElementsByTagName('canvas');
canvas.width = WINDOW_WIDTH;
canvas.height = WINDOW_HEIGHT;
canvas.style.width = `${ WINDOW_WIDTH }px`;
canvas.style.height = `${ WINDOW_HEIGHT }px`;



// const rotateOrbit = (evt) =>
// {
// 	rotateOrbitJs(-evt.movementX * 0.01, -evt.movementY * 0.01);
// };

// const stopOrbitRotation = () =>
// {
// 	window.removeEventListener('mousemove', rotateOrbit);
// 	window.removeEventListener('mouseup', stopOrbitRotation);
// };

// canvas.addEventListener
// (
// 	'mousedown',

// 	() =>
// 	{
// 		window.addEventListener('mousemove', rotateOrbit);
// 		window.addEventListener('mouseup', stopOrbitRotation);
// 	},
// );

// window.addEventListener('mouseup', stopOrbitRotation);



const canvas_context = canvas.getContext('2d');

const image_data = canvas_context.createImageData(WINDOW_WIDTH, WINDOW_HEIGHT);



window.addEventListener
(
	'load',

	async () =>
	{
		// Redundant? Does reloading of window cause killing of all processes and
		// threads spawned from them, so rendering thread does never exist
		// after reloading?
		if (!testRenderingThread())
		{
			runRenderingThread(WINDOW_WIDTH, WINDOW_HEIGHT);
		}

		let interval = null;

		await new Promise
		(
			(resolve) =>
			{
				interval =
					setInterval
					(
						() =>
						{
							if (getPixelDataStorageIsAllocated())
							{
								clearInterval(interval);

								resolve();
							}
						},

						1000,
					);
			},
		);

		const pixel_data_storage = getPixelDataStorage();

		const render = () =>
		{
			image_data.data.set(pixel_data_storage);

			canvas_context.putImageData(image_data, 0, 0);

			requestAnimationFrame(render);
		};

		render();
	},
);
